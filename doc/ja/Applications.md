# Darts-clone の使用方法

## 概要

Darts-clone を MeCab や ChaSen で利用する方法を紹介します．また，辞書がどのくらい小さくなるのかを示します．

* MeCab
 * MeCab で ipadic を用いた場合の辞書（sys.dic）
* ChaSen
 * ChaSen で ipadic を用いた場合の辞書（chadic.da）

## MeCab

### 組み込み方法

MeCab を Ubuntu 10.10 上でビルドしました．使用したのは mecab-0.98.tar.gz と mecab-ipadic-2.7.0-20070801.tar.gz の組み合わせです．これらのファイルは以下のサイトから入手できます．

* MeCab: Yet Another Part-of-Speech and Morphological Analyzer
 * http://mecab.sourceforge.net/

アーカイブのダウンロードから辞書を構築するまでの手順は以下の通りです．

1. アーカイブをダウンロードします．
 * wget http://sourceforge.net/projects/mecab/files/mecab/0.98/mecab-0.98.tar.gz
 * wget http://sourceforge.net/projects/mecab/files/mecab-ipadic/2.7.0-20070801/mecab-ipadic-2.7.0-20070801.tar.gz
2. mecab-0.98 の `darts.h` を差し替えます．
 * wget http://darts-clone.googlecode.com/svn/trunk/include/darts.h
 * tar zxf mecab-0.98.tar.gz
 * mv -f darts.h mecab-0.98/src/
3. mecab-0.98 をビルド・インストールします．
 * cd mecab-0.98
 * ./configure
  * 用いる文字コードが utf-8 のみであれば，--enable-utf8-only をオプションとして与えます．
 * make
 * make check
  * Darts-clone への差し替えに関係なく失敗しました．以前は 64-bit 環境のみ失敗していたような気がするのですが，32-bit 環境でも失敗しました．少し気になりますが，失敗しているのは run-cost-train.sh なので，とりあえず次に進みます．
 * sudo make install
 * cd ..
4. 共有ライブラリをシステムに認識させます．
 * sudo ldconfig
  * 環境によっては，/etc/ld.so.conf の編集が必要になります．辞書のインストール時に問題が起きるようであれば，/etc/ld.so.conf の最後に /usr/local/lib という行を加えてから ldconfig を実行してみてください．
5. 辞書を構築します．
 * tar zxf mecab-ipadic-2.7.0-20070801.tar.gz
 * cd mecab-ipadic-2.7.0-20070801
 * ./configure
  * 用いる文字コードが utf-8 であれば，--with-charset=utf8 を付けておき，make, sudo make install という手順でビルド・インストールするのが楽です．
 * /usr/local/libexec/mecab/mecab-dict-index -d . -o . -f EUC-JP -t 文字コード

### 辞書サイズの比較

辞書（sys.dic）のサイズは以下のようになりました．品詞や読みに割り当てられている領域の方がずっと大きいようで，Darts-clone への切り替えの効果は，辞書のサイズが 12% くらい小さくなるだけです．

|文字コード|Darts|Darts-clone 0.32g|
|---|---:|---:|
|sjis|37,638,335|33,016,639|
|euc |37,779,919|33,083,199|
|utf8|49,199,027|43,197,595|

もう少し効果がある状況として，分かち書き用の辞書も構築してみました．品詞や読みがなくなるので，切り替えの効果が高くなっています．辞書のサイズは，Darts を用いた場合の 70% 以下になっています．

|文字コード|Darts|Darts-clone 0.32g|
|---|---:|---:|
|sjis|15,132,073|10,510,377|
|euc |15,273,657|10,576,937|
|utf8|17,700,673|11,699,241|

※ 分かち書き用の辞書は mecab-dict-index に -w をオプションとして与えることで構築できます．

## ChaSen

### 組み込み方法

ChaSen を Ubuntu 10.10 にインストールしました．使用したのは chasen-2.4.4.tar.gz と ipadic-2.7.0.tar.gz の組み合わせです．これらのファイルは以下のサイトから入手できます．

* ChaSen legacy プロジェクト日本語トップページ - SourceForge.JP
 * http://sourceforge.jp/projects/chasen-legacy/
* IPAdic legacy プロジェクト日本語トップページ - SourceForge.JP
 * http://sourceforge.jp/projects/ipadic/

1. アーカイブをダウンロードします．
 * wget "http://darts-clone.googlecode.com/files/darts-clone-0.32g.tar.gz"
  * Darts であれば "http://chasen.org/~taku/software/darts/src/darts-0.32.tar.gz" になります．
 * wget "http://sourceforge.jp/frs/redir.php?m=jaist&f=%2Fchasen-legacy%2F32224%2Fchasen-2.4.4.tar.gz" -O chasen-2.4.4.tar.gz
 * wget "http://sourceforge.jp/frs/redir.php?m=iij&f=%2Fipadic%2F24435%2Fipadic-2.7.0.tar.gz" -O ipadic-2.7.0.tar.gz
2. darts-clone-0.32g をビルド・インストールします．
 * tar zxf darts-clone-0.32g.tar.gz
 * cd darts-clone-0.32g
 * ./configure
 * make
 * make check
 * sudo make install
 * cd ..
3. chasen-2.4.4 をビルド・インストールします．
 * tar zxf chasen-2.4.4.tar.gz
 * cd chasen-2.4.4
 * ./configure
 * make
 * make check
 * sudo make install
 * cd ..
4. 共有ライブラリをシステムに認識させます．
 * sudo ldconfig
  * 環境によっては，/etc/ld.so.conf の編集が必要になります．辞書のインストール時に問題が起きるようであれば，/etc/ld.so.conf の最後に /usr/local/lib という行を加えてから ldconfig を実行してみてください．
5. 辞書を構築します．
 * tar zxf ipadic-2.7.0.tar.gz 
 * cd ipadic-2.7.0/
 * ./configure
 * make
  * 後は sudo make install でインストールできます．文字コードは euc-jp になります．

文字コードを utf-8 にするときは，以下のサイトが参考になると思います．

* 「ChaSen」をUTF-8対応で導入
 * http://www.crimson-snow.net/hmsvr/centos/memo/chasen_utf8.html

### 辞書サイズの比較

ipadic-2.7.0 から構築される辞書（chadic.da）のサイズは以下のようになりました．

|文字コード|Darts|Darts-clone 0.32g|
|---|---:|---:|
|utf8|8,999,312|4,302,848|

chadic.da 以外のファイルが合計で 20MB くらいあるため，Darts-clone を用いる場合，全体の 15% くらいは削減されることになります．
