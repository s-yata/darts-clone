# Darts-clone: A clone of Darts (Double-ARray Trie System)

Darts-clone is a clone of Darts (Double-ARray Trie System)
which is a C++ header library for a static double-array trie structure.

The features of Darts-clone are as follows:

* Half-size elements
  * Darts-clone uses 32-bit elements and Darts uses 64-bit elements.
   This feature simply halves the size of dictionaries.
* Directed Acyclic Word Graph (DAWG)
  * Darts uses a basic trie to implement a dictionary.
   On the other hand, Darts-clone uses a Directed Acyclic Word Graph (DAWG)
   which is derived from a basic trie by merging its common subtrees.
   Darts-clone thus requires less elements than Darts if a given keyset
   contains many duplicate values.

Due to these features, Darts-clone can achieve better space efficiency
without degrading the search performance.

* Documentation
  * [Introduction](https://github.com/s-yata/darts-clone/blob/master/doc/en/Introduction.md)
  * [Interface](https://github.com/s-yata/darts-clone/blob/master/doc/en/Interface.md)

----

# Darts-clone: Darts（Double-ARay Trie System）のクローン

Darts-clone はダブル配列の C++ ヘッダライブラリである Darts のクローンであり，
以下のような特徴を持っています．

* 要素のサイズが半分
  * Darts が 64-bit の要素を使うのに対し， Darts-clone は 32-bit の要素を使います．
   そのため，辞書のサイズは単純に半減します．
* Directed Acyclic Word Graph (DAWG)
  * Darts がトライを木構造で表現しているのに対し，
   Darts-clone は Directed Acyclic Word Graph (DAWG) というグラフ構造を使います．
   DAWG は木構造の共通部分を併合することで得られるデータ構造なので，
   キーに関連付ける値に重複がたくさん含まれていれば，
   Darts-clone の方が少ない要素で辞書を構成できます．

これらの特徴により， Darts-clone は検索機能や速度を劣化させることなく，
よりコンパクトな辞書を実現できます．

* ドキュメント
  * [説明と使い方](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Introduction.md)
  * [インタフェース](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Interface.md)
  * [使用方法](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Applications.md)
  * [性能評価](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Evaluation.md)
  * [変更履歴](https://github.com/s-yata/darts-clone/blob/master/doc/ja/ChangeLog.md)
