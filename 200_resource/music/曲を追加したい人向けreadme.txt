譜面作成の覚書

ファイルネスト
Music->曲名ファイル->humen.txt
　　　　　　　　　|->propaty.txt
　　　　　　　　　|->曲名.wav もしくは mp3


追加の仕方

1.データベース music.db の GameMusicData に タイトル , BPM , 時間 , 譜面の1小節に係る拍子 を入れる
	sql文  insert into GameMusicData( Title , Bpm , time , Hyousi ) values (タイトル , BPM , 時間 , 譜面の1小節に係る拍子);

2.ファイルネストに従ってファイルを追加する(propaty.txtは任意、入れるとデータベースが開かなかったときもできるようになる)
	propaty.txtの中身(先頭の文字は開けない,改行で区切る)
		Bpm
		時間
		譜面の1小節に係る拍子


ショットタイプ指定方法

 1:1つだけ
 2:3方向(未実装)
 3:全方向に一度
 4:時差うち(未実装)
 5:時計回りに分割(未実装)
