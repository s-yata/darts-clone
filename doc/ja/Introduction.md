# Darts-clone の説明と使い方

## はじめに

### Darts-clone の位置づけ

Darts-clone は Darts（Double-ARray Trie System）というライブラリのクローンです．どちらもダブル配列の実装になっていますが，Darts-clone では，ダブル配列の要素を半分のサイズに押さえたことにより，辞書のサイズも半減しています．また，Darts がトライをダブル配列で実現しているのに対し，Darts-clone は DAWG（Directed Acyclic Word Graph）をダブル配列で実現しているため，キーに関連付ける値に重複が多ければ，より少ない要素で辞書を構成することができます．これらの変更によるオーバーヘッドは小さいので，検索の機能や速度を落とすことなく，辞書を小さくすることができます．

* Darts: Double-ARray Trie System
  * http://chasen.org/~taku/software/darts/

### 注意事項

Darts-clone 0.32e より前のバージョンでは，登録できるキーの数に対する制限やインタフェースの違いがありました．以降のバージョンでは解決されています．

## 使い方

Darts-clone を使う方法は，Darts と同じく，インストールしてから `#include <darts.h>` とするだけです．インストールしたくないときは，`darts.h` をコピーして `#include "darts.h"` とするだけでも問題ありません．辞書については，互換性がないので，Darts から Darts-clone への移行に際して再構築が必要になります．

Darts-clone の主要なクラスである `Darts::DoubleArray` の使い方については，[Interface](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Interface.md) を参照してください．

### MeCab への組み込み方

mecab-0.98 の場合，ソースコードのアーカイブである mecab-0.98.tar.gz を展開して，mecab-0.98/src の中にある `darts.h` を Darts-clone の `darts.h` で置き換えれば，後は通常の手順どおりにインストールできます．

インストール方法の詳細については [Applications](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Applications.md) を参照してください．

## 変更履歴

変更履歴は [ChangeLog](https://github.com/s-yata/darts-clone/blob/master/doc/ja/ChangeLog.md) にあります．

## 参考文献

関係しそうな文献を並べておきます．

* 青江 順一. ダブル配列による高速ディジタル検索アルゴリズム. **電子情報通信学会論文誌**, Vol. J71--D, No. 9, pp. 1592-1600, 1988.
* 青江 順一. 自然言語辞書の検索---ダブル配列による高速ディジタル検索アルゴリズム. **bit**, Vol. 21, No. 6, pp. 776-784, 1989.
* 青江 順一. キー検索技法：IV.トライとその応用. **情報処理**, Vol. 34, No. 2, pp 244-251, 1993.
* 森田 和宏, 泓田 正雄, 大野 将樹, 青江 順一. ダブル配列における動的更新の効率化アルゴリズム. **情報処理学会論文誌**, Vol. 42, No. 9, pp. 2229-2238, 2001.
* 大野 将樹, 森田 和宏, 泓田 正雄, 青江 順一. ダブル配列による自然言語辞書の高速更新法. **言語処理学会第11回年次大会発表論文集**, pp. 745-748, 2005.
* 矢田 晋, 森田 和宏, 泓田 正雄, 平石 亘, 青江 順一. ダブル配列におけるキャッシュの効率化. **第5回情報科学技術フォーラム（FIT2006）**, No. LD--008, pp. 71-72, 2006.
* Aoe, J. _An Efficient Digital Search Algorithm by Using a Double-Array Structure_. **IEEE Transactions on Software Engineering**, Vol. 15, No. 9, pp. 1066-1077, 1989.
* Aoe, J., Morimoto, K. & Sato, T. _An Efficient Implementation of Trie Structures_. **Software---Practice and Experience**, Vol. 22, No. 9, pp. 695-721, 1992.
* Morita, K., Fuketa, M., Yamakawa, Y. & Aoe, J. _Fast insertion methods of a double-array structure_. **Software---Practice and Experience**, Vol. 31, pp. 43-65, 2001.
* Yata, S., Oono, M., Morita, K., Fuketa, M., Sumitomo, T. & Aoe, J. _A compact static double-array keeping character codes_. **Information Processing and Management**, Vol. 43, No. 1, pp. 237-247, 2007.
* Yata, S., Morita, K., Fuketa, M. & Aoe, J. _Fast string matching with space-efficient word graphs_. **Innovations in Information Technology 2008 (IIT 2008)**, pp. 79-83, 2008.
