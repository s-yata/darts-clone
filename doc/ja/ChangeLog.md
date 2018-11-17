# Darts-clone の変更履歴

* 2018/11/17
  * [Applications](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Applications.md) を更新．
* 2011/2/13
  * Wiki の [Introduction](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Introduction.md) を更新．
* 2011/2/12
  * Wiki の [Introduction](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Introduction.md), [Interface](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Interface.md), [Applications](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Applications.md), [Evaluation](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Evaluation.md) を更新．
* 2011/2/11
  * darts-clone-0.32g.tar.gz をアップロード．
  * README, COPYING を修正．
  * darts.h のコメントを修正．
  * Wiki の [Introduction](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Introduction.md) を修正．
* 2010/10/31
  * Wiki の [Interface](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Interface.md), [Introduction](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Introduction.md), [Applications](https://github.com/s-yata/darts-clone/blob/master/doc/ja/Applications.md) を更新．
* 2010/10/30
  * darts-clone-0.32g-rc1.tar.gz をアップロード．
  * コーディング規約を変更．
  * darts.h にコメントを追加．
  * darts.h にマクロ DARTS_VERSION を追加．
* 2010/2/20
  * Wiki を更新．
* 2010/2/6
  * darts-clone-0.32g-beta2.tar.gz をアップロード．
* 2010/2/3
  * darts-clone-0.32g-beta.tar.gz をアップロード．
* 2009/7/7
  * darts-clone-0.32f.tar.gz をアップロード．
* 2009/4/1
  * darts-clone-0.32f-rc2.tar.gz をアップロード．
* 2009/2/12
  * darts-clone-0.32f-rc1.tar.gz をアップロード．
  * 速度重視．
* 2009/2/8
  * darts-clone-0.32e4.tar.gz をアップロード．
  * ダブル配列の拡張時にエラーが発生するバグを修正．
    * 1 つしかない未使用要素が先頭ブロックにある状況での問題を解決．
* 2009/2/6
  * darts-clone-0.32e3.tar.gz をアップロード．
  * ChaSen 用のコードを誤って消してしまっていたのを復活．
* 2009/1/29
  * darts-clone-0.32e2.tar.gz をアップロード．
  * 同じキーが複数あるときにダブル配列を構築できないバグを修正．
  * traverse() が探索失敗時に不正な探索位置を返すバグを修正．
* 2009/1/17
  * darts-clone-0.32e.tar.gz をアップロード．
  * 辞書の構造を変更．
    * `HugeDoubleArray` を使わなくても大規模な辞書を構築できるように変更．
    * 同じレコードが近くに配置されるときは共有するように変更．
  * `HugeDoubleArray` はサフィックスを整列しないように変更．
    * 新しい `HugeDoubleArray` は辞書順の検索に対して有効．
  * インタフェースを変更．
    * Darts-clone 専用のメソッドを削除．
* 2009/1/11
  * darts-clone-0.32d.tar.gz を再アップロード．
  * オフセットを指定して辞書を読み込むときの不具合を修正．
* 2009/1/7
  * darts-clone-0.32d.tar.gz をアップロード．
  * 構築時間を短縮．
  * 構築時のメモリ消費を削減．
* 2008/11/21
  * darts-clone-0.32c.tar.gz をアップロード．
  * traverse() を実装．
* 2008/10/13
  * darts-clone-0.32b.tar.gz をアップロード．
  * std::sort() の代わりに std::stable_sort() を使うように修正．
  * set_result() を private で static なメソッドに変更．
* 2008/10/10
  * darts-clone-0.32a.tar.gz をアップロード．
