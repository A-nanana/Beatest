//-----------------------------
// @name   add_music_scene.cpp
// @brief  描画シーン クラス
// @auther A.namami
// @date   2026/6/11  新規作成
//         2026/6/15 取り込み
// @memo   エラー型が来た場合は-1で返します
//
//Copyright (c) 2026 A.nanami All rights reserved.
//------------------------------

#include "DxLib.h"

#include "../110_drawing_tools/defining.h"
#include "../130_data_manager/134_other/color_manager.h"
#include "../130_data_manager/133_music/data_manager.h"
#include "../110_drawing_tools/text_node.h"
#include "add_music_scene.h"
#include "menu_scene.h"

//------------------------------
//ファイル名入力
//------------------------------
void FileInScene::Init()
{
	root_ = new Node();

	root_->AddChild(new TextNode("読込先ファイル名を入力(200_resource -> 220_music 内にフォルダを作って入れる,拡張子は不要)", ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), 
		line_set::brank_x, line_set::brank_y));
	next_ = this;
	camera_ = new Camera(0, 0);
	//入力作成
	input_handle_ = MakeKeyInput(system_set::tex_max, FALSE, FALSE, FALSE);
}

void FileInScene::SetUp()
{
	root_->SetWorldPositionAll();
	SetActiveKeyInput(input_handle_);

}

void FileInScene::Contact()
{
	int checker = CheckKeyInput(input_handle_);
	if (checker == 1) {
		char title_[1001];//曲タイトル

		memset(title_, 0, (system_set::tex_max + 1));
		GetKeyInputString(title_, input_handle_);
		DataManager::GetInstance()->SetTitle(title_);
		next_ = new WaitForReadScene();
	}
	else if (checker == -1) {
		next_ = new ErrScene(ErrScene::ErrId::k_input_err);

	}
	
}

Scene* FileInScene::Update(float delta_time)
{
	Contact();
	root_->UpdateAll(delta_time);
	return next_;
}

void FileInScene::Draw(int window_handle)
{
	root_->DrawAll(window_handle,camera_);
	DrawKeyInputString(line_set::brank_x, line_set::brank_y * 2, input_handle_);
}

void FileInScene::Finalize()
{
	DeleteKeyInput(input_handle_);
	root_->ReleaseResourceAll();
}


//------------------------------
//待機シーン
//------------------------------

WaitScene::WaitScene(std::vector<std::string> texts)
{
	for (auto tex : texts) {
		show_text_.push_back(tex);
	}
}

void WaitScene::Init()
{
	root_ = new Node();

	int i = 0;//行計算用
	for (auto tex : show_text_) {
		root_->AddChild(new TextNode( tex.c_str(), ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), line_set::brank_x, line_set::brank_y * i + line_set::brank_y));
		++i;
	}
	next_ = this;
	camera_ = new Camera(0, 0);

}

void WaitScene::SetUp()
{
	root_->SetWorldPositionAll();
}

Scene* WaitScene::Update(float delta_time)
{
	Contact();
	root_->UpdateAll(delta_time);
	return next_;
}

void WaitScene::Draw(int window_handle)
{
	root_->DrawAll(window_handle,camera_);
}

void WaitScene::Finalize()
{
	root_->ReleaseResourceAll();
}

//------------------------------
//変換内容入力シーン
//------------------------------
void InputDataScene::Init()
{
	for (int i = 0; i < Fase::k_max; i++) {
		root_[i] = new Node();
	}

	root_[Fase::k_input_bpm]->AddChild(new TextNode( "Bpmを入力",ColorManager::GetInstance()->SerchColor(string_set::font_nomal1),  line_set::brank_x,line_set::brank_y ));
	root_[Fase::k_input_hakusuu]->AddChild(new TextNode( "1小節の拍子数(基本はbpmのカウント方式に準拠)",  ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), 
		line_set::brank_x,line_set::brank_y));
	next_ = this;
	fase_ = Fase::k_input_bpm;
	//入力作成
	input_handle_ = MakeKeyInput(system_set::tex_max, FALSE, FALSE, TRUE);
	input_data_ = new MusicMakerWant ();
	camera_ = new Camera(0, 0);

}

void InputDataScene::SetUp()
{
	for (int i = 0; i < Fase::k_max; i++) {
		root_[i]->SetWorldPositionAll();
	}
	SetActiveKeyInput(input_handle_);

}

void InputDataScene::Contact()
{
	int checker = CheckKeyInput(input_handle_);
	//入力の完了
	if (checker == 1) {
		//状況確認
		switch (fase_)
		{
		case Fase::k_input_bpm:
			input_data_->bpm = GetKeyInputNumber(input_handle_);
			SetActiveKeyInput(input_handle_);

			break;
		case Fase::k_input_hakusuu:
			input_data_->hakusuu = GetKeyInputNumber(input_handle_);

			DeleteKeyInput(input_handle_);
			input_handle_ = MakeKeyInput(system_set::tex_max, FALSE, FALSE, FALSE);
			SetActiveKeyInput(input_handle_);

			DataManager::GetInstance()->SetMusicMakerWant (input_data_);
			input_data_ = nullptr;
			next_ = new WaitForWriteScene();
			break;
		default:
			break;
		}

		//フェーズを進める
		++fase_;

	}
	else if (checker == -1) {
		next_ = new ErrScene(ErrScene::ErrId::k_input_err);
	}

}

Scene* InputDataScene::Update(float delta_time)
{
	Contact();
	//終わってないなら更新
	if (fase_ < Fase::k_max) {
		root_[fase_]->UpdateAll(delta_time);
	}
	return next_;
}

void InputDataScene::Draw(int window_handle)
{
	root_[fase_]->DrawAll(window_handle,camera_);
	DrawKeyInputString(line_set::brank_x, line_set::brank_y * 2, input_handle_);
}

void InputDataScene::Finalize()
{
	DeleteKeyInput(input_handle_);
	for (int i = 0; i < Fase::k_max; i++) {
		root_[i]->ReleaseResourceAll();
	}
}


//------------------------------
//終了シーン
//------------------------------
void EndScene::Init()
{
	root_ = new Node();

	root_->AddChild(new TextNode( "完成しました！Outputファイル内を確認してください！", ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), line_set::brank_x,line_set::brank_y));
	root_->AddChild(new TextNode("適当なキーで終了", ColorManager::GetInstance()->SerchColor(string_set::font_nomal1), line_set::brank_x,line_set::brank_y*2));
	next_ = this;
	camera_ = new Camera(0, 0);
}

void EndScene::SetUp()
{
	root_->SetWorldPositionAll();
}

void EndScene::Contact()
{
	//キー確認
	if (CheckHitKeyAll() != 0) {
		DataManager::GetInstance()->SetEnd(true);
		next_ = new MenuScene();
	}
}

Scene* EndScene::Update(float delta_time)
{
	Contact();
	root_->UpdateAll(delta_time);
	return next_;
}

void EndScene::Draw(int window_handle)
{
	root_->DrawAll(window_handle,camera_);
}

void EndScene::Finalize()
{
	root_->ReleaseResourceAll();
}
//------------------------------
//待機シーン派生
//------------------------------
void WaitForReadScene::Contact()
{
	if (DataManager::GetInstance()->GetFinRead()) {
		next_ = new InputDataScene();
		updata_sub_thred_.wait();
	}

}

bool WaitForReadScene::Reading()
{
	//読込
	std::string title = DataManager::GetInstance()->GetTitle();
	WavData* data = new WavData();
	int* tag = new int();
	int* length = new int();
	//読み込み
	std::string get_file(file_set::music_data_file_pass);
	{
		get_file.append(title);
		get_file.append("/");
		get_file.append(title);
	}
	bool check = MusicMaker::GetInstance()->GetFile(&get_file, data, tag, length);
	//結果確認
	if (!check) {
		next_ = new ErrScene(ErrScene::ErrId::k_read_err);
	}

	//代入
	DataManager::GetInstance()->SetWav(data);
	DataManager::GetInstance()->SetMaker(new Maker());
	DataManager::GetInstance()->SetTagTime(*tag);
	DataManager::GetInstance()->SetTime(*length);

	DataManager::GetInstance()->SetFinRead(true);
	std::cout << "ok\n";

	return true;
}

void WaitForReadScene::Init()
{
	DataManager::GetInstance()->SetFinRead(false);
	WaitScene::Init();
	updata_sub_thred_ = std::async(&WaitForReadScene::Reading, this);

}


Scene* WaitForReadScene::Update(float delta_time)
{
	Contact();
	return next_;
}

void WaitForWriteScene::Init()
{
	DataManager::GetInstance()->SetFinWrite(false);
	WaitScene::Init();
	updata_sub_thred_ = std::async(&WaitForWriteScene::Writing, this);


}

void WaitForWriteScene::Contact()
{

	if (DataManager::GetInstance()->GetFinWrite()) {
		next_ = new EndScene();
		updata_sub_thred_.wait();
	}
}

bool WaitForWriteScene::Writing()
{
	//データ作成
	WavData data = DataManager::GetInstance()->GetWav();
	MusicMakerWant  music = DataManager::GetInstance()->GetMusicMakerWant();
	std::string title = DataManager::GetInstance()->GetTitle();
	int tag_t = DataManager::GetInstance()->GetTagTimr();
	int length = DataManager::GetInstance()->GetTime();
	bool to_write = true;//書き込み可否
	std::uint8_t flgs = 0;//難易度フラグ

	//難易度分繰り返し
	for (int i = 0; i < system_set::defficulter_max; i++) {
		std::string* writing_data = DataManager::GetInstance()->GetMaker().MakeHumen(&data, music.bpm, i, music.hakusuu, tag_t, length);

		//書き込み
		std::string get_file(file_set::music_data_file_pass);
		{
			get_file.append(title);
			get_file.append("/");
			get_file.append(string_set::defficult[i]);
			get_file.append(".txt");
		}
		bool check = MusicMaker::GetInstance()->WriteFile(&get_file, writing_data);
		//結果確認
		if (!check) {
			next_ = new ErrScene(ErrScene::ErrId::k_write_err);
			to_write = false;
			break;
		}
		flgs |= 1 << i;
	}
	//情報書き込み可否
	if (to_write) {
		//書き込み
		if (!MusicMaker::GetInstance()->WritePropaty(&title, &music, length, flgs)) {
			next_ = new ErrScene(ErrScene::ErrId::k_write_err);
		}
	}
	DataManager::GetInstance()->SetFinWrite(true);
	return true;
}

Scene* WaitForWriteScene::Update(float delta_time)
{
	Contact();
	return next_;
}

void ErrScene::Init()
{
	std::string add_text("エラー番号 : ");
	add_text.append(std::to_string(err_nun_));
	show_text_.push_back(add_text);
	WaitScene::Init();
}

void ErrScene::Contact()
{
	//キー確認
	if (CheckHitKeyAll() != 0) {
		DataManager::GetInstance()->SetEnd(true);
		next_ = new MenuScene();
	}
}

Scene* ErrScene::Update(float delta_time)
{
	Contact();
	root_->UpdateAll(delta_time);
	return next_;
}
