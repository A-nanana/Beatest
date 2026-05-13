# Beatest

## 概要

## 制作情報

* 制作期間: 2026年2月～2026年5月
* 開発人数: 1人
* 担当範囲: 企画、実装、デバッグ、UI作成、一部素材

## 使用技術

* C++
* Dxライブラリ
* Visual Studio
* Git

## 工夫した点

* SQLiteを使用した楽曲の読み込み、書き込み
  * 曲情報、難易度、ハイスコアのテーブルにそれぞれ内容を記録、呼び出しています。
  * これにより、SQLiteでの簡単なテーブル操作だけで内容を変えられるようにしています。
* 継承を利用したクラス作成

  * 基底クラスに全体として必要な関数を入れることで、呼び出しで書く関数を少なくしました。
  * 登録すれば呼び出し忘れが無くなるようになっています。
* `std::unrodered_map`を利用した画像の読み込み回数の減少

  * 読み込んだ画像を`GraphRoader`クラスの`std::unordered\_map<std::string, int> graph\_`内に保管するようにしました。
  * 同じ画像を複数回読み込まないようにし、画像読み込み時間の短縮を図っています。

## 起動方法

1. `Beatest.sln`をVisual Studioで開く。
2. RelaseまたはDebugでビルドする。
3. 2.で生成された`exe`ファイルを起動する。

## 操作方法

**<ゲーム中>**

* W : 上移動
* S : 下移動
* A : 左移動
* D : 右移動
* P : 一時停止

**<ゲーム外>**

* W A S D : それぞれ項目切り替え

  * A , D については設定画面のみ数値変更となります。
* Enter : 決定

## 備考、不具合

* レーザーの回避判定が不安定です。
* 楽曲「初詣」はテストプレイ用に楽曲時間が10秒に設定されています。
* ソースの著作権表記はドキュメントファイル内の`著作権表記`に記載しています。
  
## 参考資料、各種ライブラリ
  
**ライブラリ**    

* [ＤＸライブラリ置き場](https://dxlib.xsrv.jp/index.html)  
* [SQLite](https://sqlite.org/index.html)  

**参考資料**  
  
* [@yukikoblog8376(yukiko@一流のIT研修講師を目指し学習中)](https://qiita.com/yukikoblog8376)様
  * [【保存版】単体テスト仕様書の作り方完全ガイド - テンプレート・チェックシート付き](https://qiita.com/yukikoblog8376/items/584c8748feec931926a3#-%E5%9F%BA%E6%9C%AC%E3%83%86%E3%83%B3%E3%83%97%E3%83%AC%E3%83%BC%E3%83%88%E6%A8%AA%E5%9E%8B)  
  
* [理数アラカルト](https://risalc.info/)様
  * [外積の長さ = 平行四辺形の面積](https://risalc.info/src/cross-product-parallelogram-area.html)  
  
* [無職の学び舎](https://www.nekonecode.com/)様
  * [点と矩形(回転あり)の衝突](https://www.nekonecode.com/math-lab/pages/collision2/point-and-box/)  

## 著作権表記
　libjpeg　Copyright (C) 1991-2013, Thomas G. Lane, Guido Vollbeding.
　　　this software is based in part on the work of the Independent JPEG Group


　　　libpng　Copyright (C) 2004, 2006-2012 Glenn Randers-Pehrson.
　　　zlib　Copyright (C) 1995-2012 Jean-loup Gailly and Mark Adler.


　　　libtiff　Copyright (c) 1988-1997 Sam Leffler
　　　libtiff　Copyright (c) 1991-1997 Silicon Graphics, Inc.

　　　Permission to use, copy, modify, distribute, and sell this software and
　　　its documentation for any purpose is hereby granted without fee, provided
　　　that (i) the above copyright notices and this permission notice appear in
　　　all copies of the software and related documentation, and (ii) the names of
　　　Sam Leffler and Silicon Graphics may not be used in any advertising or
　　　publicity relating to the software without the specific, prior written
　　　permission of Sam Leffler and Silicon Graphics.

　　　THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
　　　EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
　　　WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

　　　IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
　　　ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
　　　OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
　　　WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
　　　LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
　　　OF THIS SOFTWARE.


　　　libogg　Copyright (C) 2002-2009 Xiph.org Foundation

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　- Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　- Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　- Neither the name of the Xiph.org Foundation nor the names of its
　　　contributors may be used to endorse or promote products derived from
　　　this software without specific prior written permission.

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
　　　SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
　　　LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
　　　OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Opus audio codec
　　　Copyright 2001-2011 Xiph.Org, Skype Limited, Octasic,
　　　 Jean-Marc Valin, Timothy B. Terriberry,
　　　 CSIRO, Gregory Maxwell, Mark Borgerding,
　　　 Erik de Castro Lopo

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　- Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　- Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　- Neither the name of Internet Society, IETF or IETF Trust, nor the
　　　names of specific contributors, may be used to endorse or promote
　　　products derived from this software without specific prior written
　　　permission.

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
　　　EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
　　　PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
　　　PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
　　　LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
　　　NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
　　　SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Opusfile
　　　Copyright (c) 1994-2013 Xiph.Org Foundation and contributors

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　- Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　- Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　- Neither the name of the Xiph.Org Foundation nor the names of its
　　　contributors may be used to endorse or promote products derived from
　　　this software without specific prior written permission.

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
　　　SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
　　　LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
　　　OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Mersenne Twister
　　　Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
　　　All rights reserved.

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　1. Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　2. Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　3. The name of the author may not be used to endorse or promote products
　　　derived from this software without specific prior written permission.

　　　THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
　　　IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
　　　OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
　　　IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
　　　INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
　　　NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
　　　THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Bullet　Copyright (c) 2003-2006 Erwin Coumans.

      DX Library Copyright (C) 2001-2025 Takumi Yamada.

 
