# Darts-clone のインタフェース

## 概要

Darts-clone は単一のヘッダファイル（`darts.h`）で構成されるライブラリです．そのため，`#include <darts.h>` を挿入するだけで，すべての機能を使うことができます．一般的なアプリケーションでは，`Darts::DoubleArray` というクラスを使うことになります．

`Darts::DoubleArray` を利用する場合，Darts-clone のインタフェースは Darts とほとんど同じになります．そのため，Darts を用いているアプリケーションの大半については，`darts.h` を差し替えるだけで，簡単に Darts から Darts-clone へと移行できると思います．

## 辞書クラス

Darts-clone の利用において，外部からアクセスするクラスは `Darts::DoubleArray` のみです．`Darts::DoubleArray` はテンプレートクラスである `Darts::DoubleArrayImpl` の代表的なインスタンスの別名になっています．互換性の問題でもない限り，直接 `Darts::DoubleArrayImpl` を利用する機会はありません．

```cpp
namespace Darts {

class DoubleArray {
 public:
  typedef int value_type;
  typedef char key_type;
  typedef value_type result_type;  // for compatibility.

  struct result_pair_type {
    value_type value;
    std::size_t length;
  };

  DoubleArray();
  ~DoubleArray();

  void set_array(const void *ptr,
                 std::size_t size = 0);
  const void *array() const;

  void clear();

  std::size_t unit_size() const;
  std::size_t size() const;
  std::size_t total_size() const;
  std::size_t nonzero_size() const;

  int build(std::size_t num_keys,
            const key_type * const *keys,
            const std::size_t *lengths = NULL,
            const value_type *values = NULL,
            int (*progress_func)(std::size_t, std::size_t) = NULL);

  int open(const char *file_name,
           const char *mode = "rb",
           std::size_t offset = 0,
           std::size_t size = 0);

  int save(const char *file_name,
           const char *mode = "wb",
           std::size_t offset = 0) const;

  template <class U>
  void exactMatchSearch(const key_type *key,
                        U &result,
                        std::size_t length = 0,
                        std::size_t node_pos = 0) const;
  template <class U>
  U exactMatchSearch(const key_type *key,
                     std::size_t length = 0,
                     std::size_t node_pos = 0) const;

  template <class U>
  std::size_t commonPrefixSearch(const key_type *key,
                                 U *results,
                                 std::size_t max_num_results,
                                 std::size_t length = 0,
                                 std::size_t node_pos = 0) const;

  value_type traverse(const key_type *key,
                      std::size_t &node_pos,
                      std::size_t &key_pos,
                      std::size_t length = 0) const;

 private:
  // Disallows copy and assignment.
  DoubleArray(const DoubleArray &);
  DoubleArray &operator=(const DoubleArray &);
};

}  // namespace Darts
```

### テンプレート引数

`DoubleArray` の元になっている `DoubleArrayImpl` は 4 つのテンプレート引数を受けとるようになっていますが，実際に使うのは 3 番目だけです．残る 3 つのテンプレート引数は，互換性のためだけに残されています．`DoubleArray` については，`DoubleArrayImpl<void, void, int, void>` の別名になっています．

第 3 テンプレート引数については，各キーに関連付ける値の型を指定するために利用されます．ただし，Darts-clone が内部で用いる値の型は変更されないので，値の受け渡しにおいて `static_cast` がフィルタとして利用されるだけです．`long long` を指定しても 31-bit 精度のままであり，`float` を指定しても整数に丸められてしまいます．

### 型

検索結果を受け取るための型としては，`Darts::DoubleArray::result_type` と `Darts::DoubleArray::result_pair_type` の 2 種類が用意されています．前者の `Darts::DoubleArray::result_type` は `Darts::DoubleArray::value_type` の別名であり，検索において，マッチしたキーに関連付けられている値を受け取るために使います．後者の `Darts::DoubleArray::result_pair_type` は，検索においてマッチしたキーについて，関連付けられた値だけでなく長さも取得したいという状況で使うようになっています．

```cpp
struct result_pair_type {
  value_type value;
  std::size_t length;
};
```

検索条件にマッチするキーが見つからない場合，`exactMatchSearch()` は `value` に `static_cast<value_type>(-1)` を代入し，`length` に `0` を代入します．他方，マッチするキーが見つかった場合，`value` にマッチしたキーに関連付けられている値を代入し，`length` にマッチしたキーの長さを代入するようになっています．

### メソッド

#### コンストラクタとデストラクタ

```cpp
DoubleArray();
```

コンストラクタはメンバの初期化のみをおこないます．初期化子を使って `0` と `NULL` を代入するだけなので，失敗することはありません．

```cpp
~DoubleArray();
```

デストラクタは `clear()` を呼び出すだけです．`clear()` の内部では，ダブル配列に対して割り当てられたメモリの解放とメンバの初期化がおこなわれます．`set_array()` を使って割り当てられたメモリは解放されません．

#### 配列の設定と取得

```cpp
void set_array(const void *ptr,
               std::size_t size = 0);
```

`set_array()` はダブル配列の開始アドレスを設定するメソッドです．`mmap()` を使ってダブル配列をメモリ上にマップした場合などに有効です．同時に要素数も設定できるようになっていますが，検索に要素数は不要なので，省略しても特に問題はありません．ただし，`size()` と `total_size()` が `0` を返すようになる点には注意が必要です．

`set_array()` により設定した領域は `clear()` を呼び出しても解放されないので，呼び出し側で適切にメモリを管理しなければなりません．

```cpp
const void *array() const;
```

`array()` はダブル配列の開始アドレスを返します．`array()` と `total_size()` を組み合わせれば，ダブル配列の領域を取得することができます．`set_array()` で要素数を指定しなかったときは `total_size()` が `0` になってしまうので注意してください．

#### メモリの解放と初期化

```cpp
void clear();
```

`clear()` は，`build()` もしくは `open()` によって割り当てられたメモリを解放し，メンバの初期化をおこないます．`clear()` により初期化したオブジェクトは，コンストラクタにより初期化した直後と同じ状態になります．`set_array()` により設定された領域は解放されないことに注意してください．

#### サイズの取得

```cpp
std::size_t unit_size() const;
std::size_t size() const;
std::size_t total_size() const;
std::size_t nonzero_size() const;
```

`unit_size()`, `size()`, `total_size()`, `nonzero_size()` はダブル配列を構成する各要素のサイズや要素数などを返します．各メソッドの返す値は以下のようになっています．

|メソッド|戻り値|
|---|---|
|`unit_size()`|各要素のサイズ（`4` bytes）|
|`size()`|要素数†|
|`total_size()`|ダブル配列のサイズ（`size() * unit_size()` bytes）†|
|`nonzero_size()`|要素数‡|

† `set_array()` によりアドレスを設定する場合，要素数も一緒に設定しておかないと，`size()` や `total_size()` により正しいサイズを取得できなくなります．

‡ Darts の `nonzero_size()` は使用状態になっている要素の数を返しますが，Darts-clone の `nonzero_size()` は常に要素数を返すようになっています．Darts-clone では未使用要素の計数が難しいことが理由です．

#### ダブル配列の構築

```cpp
int build(std::size_t num_keys,
          const key_type * const *keys,
          const std::size_t *lengths = NULL,
          const value_type *values = NULL,
          int (*progress_func)(std::size_t, std::size_t) = NULL);
```

`build()` はダブル配列を構築するメソッドです．`num_keys` には登録するキーの数，`keys` には登録するキーの配列，`lengths` には登録するキーの長さを配列にしたもの，`values` には登録するキーに関連付ける値の配列，`progress_func` には進捗状況の受け取りに用いるコールバック関数を指定するようになっています．

`lengths` が `NULL` であれば，`keys` は NULL 文字（`'\0'`）を終端とする文字列の配列として扱われます．また，`values` が `NULL` であれば，各キーには `keys` におけるインデックスが関連付けられます．つまり，`i` 番目のキーには `i - 1` が関連付けられることになります．最後に，`progress_func` が `NULL` であれば，コールバックによる進捗状況の報告は無効になります．

`keys`, `lengths`, `values` には，いくつかの制約があります．まず，`keys` は昇順に整列しておく必要があります．次に，`lengths` により長さを指定した場合，文字列中に NULL 文字（`'\0'`）が含まれてはならないという制約が発生します．`values` については，非負の値しか設定できないという制約があります．これらの制約にひっかかったり，メモリを確保できなかったりすると，`Darts::Details::Exception` が例外として送出されます．`Darts::Details::Exception` は `std::exception` の派生クラスなので，`what()` によりエラーメッセージを取得できます．

同じキーが含まれる場合は先頭に近い方が採用されることに注意してください．

`progress_func` は進捗状況を引数として受け取ります．第 1 引数が進捗を示す値，第 2 引数が完成した段階で到達する値です．例えば，進捗状況を百分率で表示するなら，（`100.0 * the_1st_argument / the_2nd_argument`）を使います．

ダブル配列の構築に成功した場合，`build()` は `0` を返します．失敗すると例外を投げるので，返り値は常に `0` になります．

#### ダブル配列の読み込み

```cpp
int open(const char *file_name,
         const char *mode = "rb",
         std::size_t offset = 0,
         std::size_t size = 0);
```

`open()` はダブル配列をファイルから読み込みます．`file_name` にはファイル名，`mode` にはファイルのモード，`offset` には読み込み前にスキップするバイト数，`size` には読み込むバイト数を指定するようになっています．`size` が `0` のときは，`offset` からファイルの終端までをダブル配列として読み込みます．

`open()` の返り値は，成功すると `0` になり，失敗すると `-1` になります．また，メモリの確保に失敗して `Darts::Details::Exception` を送出する場合があります．

#### ダブル配列の保存

```cpp
int save(const char *file_name,
         const char *mode = "wb",
         std::size_t offset = 0) const;
```

`save()` はダブル配列をファイルに保存します．`file_name` にはファイル名，`mode` にはファイルのモード，`offset` には書き込み前にスキップするバイト数を指定するようになっています．

`save()` の返り値は，成功すると `0` になり，失敗すると `-1` になります．

#### 完全一致するキーの検索

```cpp
template <class U>
void exactMatchSearch(const key_type *key,
                      U &result,
                      std::size_t length = 0,
                      std::size_t node_pos = 0) const;
```

`exactMatchSearch()` は入力文字列に一致するキーが登録されているかどうかを確認します．

`key` には入力文字列，`result` には結果を受け取るためのオブジェクト，`length` には入力文字列の長さ，`node_pos` にはダブル配列の探索開始位置を指定するようになっています．`length` が `0` の場合，`key` は NULL 文字（`'\0'`）を終端とする文字列として扱われます．`node_pos` には `traverse()` で取得した探索位置を指定することもできますが，基本的にはダブル配列の初期状態を示す `0` を指定するようになっています．

`result` の型としては，`Darts::DoubleArray::result_type` と `Darts::DoubleArray::result_pair_type` が利用できます．`result_type` を指定すると，キーに関連付けられている値のみが取得できます．`result_pair_type` を指定すると，一致したキーの長さも併せて取得できます．ただし，実際に取得できるのは `node_pos` から状態遷移した回数であり，`node_pos` が `0` でない場合，キーの長さとは一致しません．

一致するキーが登録されていない場合，本来はキーに関連付けられている値が格納されるべきところに，代わりに `-1` が格納されます．

```cpp
template <class U>
U exactMatchSearch(const key_type *key,
                   std::size_t length = 0,
                   std::size_t node_pos = 0) const;
```

動作は上述の `exactMatchSearch()` と同じですが，結果を引数に格納するのではなく，返り値にするようになっています．

#### 文字列の前方部分に一致するキーの検索

```cpp
template <class U>
std::size_t commonPrefixSearch(const key_type *key,
                               U *results,
                               std::size_t max_num_results,
                               std::size_t length = 0,
                               std::size_t node_pos = 0) const;
```

`commonPrefixSearch()` は入力文字列の前半部分に一致するキーを列挙します．

`key` には入力文字列，`results` には結果を受け取るための配列，`max_num_results` には受け取る結果の数に対する上限，`length` には入力文字列の長さ，`node_pos` にはダブル配列の探索開始位置を指定するようになっています．`length` が `0` の場合，`key` は NULL 文字（`'\0'`）を終端とする文字列として扱われます．`node_pos` には `traverse()` で取得した探索位置を指定することもできますが，基本的にはダブル配列の初期状態を示す `0` を指定するようになっています．

返り値は検索条件にマッチするキーの数になります．検索条件にマッチするキーの数が `max_num_results` より大きいときは，`max_num_results` 番目までが `results` に格納され，返り値は `max_num_results` より大きな値になります．

```cpp
value_type traverse(const key_type *key,
                    std::size_t &node_pos,
                    std::size_t &key_pos,
                    std::size_t length = 0) const;
```

`traverse()` はダブル配列上で入力文字列に対する状態遷移をおこないます．

`key` には入力文字列，`node_pos` には遷移前の状態，`key_pos` には入力文字列のマッチング開始位置，`length` には入力文字列の長さを指定するようになっています．基本的に，`node_pos` にはダブル配列の初期状態である `0` を設定して渡すことになります．入力文字列の先頭からマッチングをおこなう場合，`key` には `0` を設定して渡すことになります．`length` が `0` の場合，`key` は NULL 文字（`'\0'`）を終端とする文字列として扱われます．

途中で状態遷移に失敗したときは `-2` が返り値になります．最後まで無事に状態遷移できたときは，最終的に到達した状態によって返り値が変化します．遷移によって到達した状態が受容状態でなければ返り値は `-1` です．受容状態であれば，その状態と対応するキーに関連付けられている値が返り値になります．つまり，検索に成功したときは `0` 以上の値になり，検索に失敗したときは負の値になります．

`traverse()` の内部では，状態遷移に成功する度に `node_pos` と `key_pos` が更新されます．この機能を利用すると，到達した状態から `traverse()` により継続して状態遷移を試したり，特定のプレフィックスを持つキーの確認を効率化したりすることが可能です．

#### コピーコンストラクタと代入演算子

```cpp
DoubleArray(const DoubleArray &);
DoubleArray &operator=(const DoubleArray &);
```

コピーコンストラクタと代入演算子は禁止されています．
