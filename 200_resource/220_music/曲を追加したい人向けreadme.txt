譜面作成の覚書

ファイルネスト
Music->曲名ファイル->各種譜面テキストファイル
　　　　　　　　　|->propaty.txt
　　　　　　　　　|->曲名.wav もしくは mp3


追加の仕方

1.データベース music.db の GameMusicData に タイトル , BPM , 時間 , 譜面の1小節に係る拍子 を入れる
	sql定型文  insert into GameMusicData( Title , Bpm , time , Hyousi ) values (タイトル , BPM , 時間 , 譜面の1小節に係る拍子 );

        その後、次のsql文で楽曲idを確認してください.
        sql定型文　select MusicKey, title from GameMusicData WHERE title = '曲の名前';
        
	左の列の出てくるのが楽曲idです。


2.データベース music.db の GameMusicData に タイトル , BPM , 時間 , 譜面の1小節に係る拍子 を入れる
	sql定型文  insert into Defficult(MusicKey, Easy, Nomal, Hard, Beyond) values(割り振られたid, 譜面の存在フラグ, 譜面の存在フラグ, 譜面の存在フラグ, 譜面の存在フラグ);

        また、こちらはデフォルトでNomal難易度のみ認識するようになっています。
　　　　それで十分であるならこちら。
        sql定型文  insert into Defficult(MusicKey) values(割り振られたid);


3.ファイルネストに従ってファイルを追加する(propaty.txtは任意、入れるとデータベースが開かなかったときもできるようになる)
	propaty.txtの中身(先頭の文字は開けない,改行で区切る)
		Bpm
		時間
		譜面の1小節に係る拍子


＜各種譜面テキストファイルについて＞

　・難易度毎に作成してください。
　・難易度毎のファイル名は以下の通りです。

　　Easy   -> Easy.txt
    Nomal  -> Nomal.txt
    Hard   -> Hard.txt
    Beyond -> Beyond.txt

　・ノーツタイプ指定方法

 1:1つだけ
 2:3方向(未実装)
 3:全方向に一度
 4:時差うち(未実装)
 5:時計回りに分割(未実装)


 