# Darts-clone の使用方法

## 概要

Darts-clone を MeCab や ChaSen で利用する方法を紹介します．また，辞書がどのくらい小さくなるのかを示します．

* MeCab
  * MeCab で ipadic を用いた場合の辞書（sys.dic）
* ChaSen
  * ChaSen で ipadic を用いた場合の辞書（chadic.da）

## MeCab

### 組み込み方法

MeCab を Ubuntu 18.04 上でビルドしました．使用したのは mecab-0.996.tar.gz と mecab-ipadic-2.7.0-20070801.tar.gz の組み合わせです．これらのファイルは以下のサイトから入手できます．

* MeCab: Yet Another Part-of-Speech and Morphological Analyzer
  * https://taku910.github.io/mecab/

アーカイブのダウンロードから辞書を構築するまでの手順は以下の通りです．

1. アーカイブをダウンロードします．
   * wget -O mecab-0.996.tar.gz 'https://drive.google.com/uc?export=download&id=0B4y35FiV1wh7cENtOXlicTFaRUE'
   * wget -O mecab-ipadic-2.7.0-20070801.tar.gz 'https://drive.google.com/uc?export=download&id=0B4y35FiV1wh7MWVlSDBCSXZMTXM'
2. mecab-0.996 の `darts.h` を差し替えます．
   * wget 'https://raw.githubusercontent.com/s-yata/darts-clone/master/include/darts.h'
   * tar zxf mecab-0.996.tar.gz
   * mv -f darts.h mecab-0.996/src/darts.h
3. mecab-0.996 をビルド・インストールします．
   * cd mecab-0.996
   * ./configure
     * 用いる文字コードが utf-8 のみであれば，--enable-utf8-only をオプションとして与えます．
   * make
   * make check
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

ChaSen を Ubuntu 18.04 にインストールしました．使用したのは chasen-2.4.5.tar.gz と ipadic-2.7.0.tar.gz の組み合わせです．これらのファイルは以下のサイトから入手できます．

* chasen legacy -- an old morphological analyzer
  * https://chasen-legacy.osdn.jp/
* IPAdic legacy プロジェクト日本語トップページ - OSDN
  * https://ja.osdn.net/projects/ipadic/

1. アーカイブをダウンロードします．
   * wget "http://darts-clone.googlecode.com/files/darts-clone-0.32g.tar.gz"
     * Darts であれば "http://chasen.org/~taku/software/darts/src/darts-0.32.tar.gz" になります．
   * wget -O chasen-2.4.5.tar.xz 'https://ja.osdn.net/frs/redir.php?m=jaist&f=chasen-legacy%2F56305%2Fchasen-2.4.5.tar.xz'
   * wget -O ipadic-2.7.0.tar.gz 'http://sourceforge.jp/frs/redir.php?m=iij&f=%2Fipadic%2F24435%2Fipadic-2.7.0.tar.gz'
2. darts-clone をビルド・インストールします．
   * git clone 'https://github.com/s-yata/darts-clone.git'
   * cd darts-clone
   * autoreconf -i
   * ./configure
   * make
   * make check
   * sudo make install
   * cd ..
3. chasen-2.4.5 をビルド・インストールします．
   * tar Jxf chasen-2.4.5.tar.gz
   * cd chasen-2.4.5
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

文字コードを utf-8 にするときは，以下のページが参考になると思います．

* ChaSenをUTF-8用にインストール - Qiita
  * https://qiita.com/noobar/items/39583f54d9a7e4ffe655

### 辞書サイズの比較

ipadic-2.7.0 から構築される辞書（chadic.da）のサイズは以下のようになりました．

|文字コード|Darts|Darts-clone|
|---|---:|---:|
|utf8|8,999,312|4,302,848|

chadic.da 以外のファイルが合計で 20MB くらいあるため，Darts-clone を用いる場合，全体の 15% くらいは削減されることになります．
