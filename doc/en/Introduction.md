# Darts-clone Introduction

## Introduction

### What's Darts-clone

Darts-clone is a clone of Darts (Double-ARray Trie System). Both are implementations of double-array structure, but Darts-clone makes dictionaries more compact. This advantage is due to the following improved features.

* Half-size units
  * While Darts allocates 8 bytes to each unit, Darts-clone allocates only 4 bytes to each unit. This feature simply halves the size of dictionaries.
* More sophisticated structure
  * While Darts uses a trie to implement a dictionary, Darts-clone uses a Directed Acyclic Word Graph (DAWG), which is derived from a trie by merging its common subtrees. Darts-clone thus requires less units than Darts if a given keyset contains many duplicate values.

These features enable Darts-clone to build more compact dictionaries without degrading search performance.

* Darts: Double-ARray Trie System
  * http://chasen.org/~taku/software/darts/

### Notes

Early versions of Darts-clone, earlier than 0.32e, have limitations in the number of keys. Also, the early Darts-clones have a little different interfaces from the interface of Darts.

Darts-clone 0.32e or later works as well as Darts.

## How To

To use Darts-clone, please install Darts-clone and include the Darts-clone's header `#include <darts.h>`. If you don't want to install Darts-clone, please copy `darts.h` to the directory where your C++ source files exist and then include the Darts-clone's header `#include "darts.h"`. Please see also [Interface](https://github.com/s-yata/darts-clone/blob/master/doc/en/Interface.md).

Note that Darts/Darts-clone dictionary files are not compatible.

## References

### English

* Aoe, J. _An Efficient Digital Search Algorithm by Using a Double-Array Structure_. **IEEE Transactions on Software Engineering**, Vol. 15, No. 9, pp. 1066-1077, 1989.
* Aoe, J., Morimoto, K. & Sato, T. _An Efficient Implementation of Trie Structures_. **Software---Practice and Experience**, Vol. 22, No. 9, pp. 695-721, 1992.
* Morita, K., Fuketa, M., Yamakawa, Y. & Aoe, J. _Fast insertion methods of a double-array structure_. **Software---Practice and Experience**, Vol. 31, pp. 43-65, 2001.
* Yata, S., Oono, M., Morita, K., Fuketa, M., Sumitomo, T. & Aoe, J. _A compact static double-array keeping character codes_. **Information Processing and Management**, Vol. 43, No. 1, pp. 237-247, 2007.
* Yata, S., Morita, K., Fuketa, M. & Aoe, J. _Fast string matching with space-efficient word graphs_. **Innovations in Information Technology 2008 (IIT 2008)**, pp. 79-83, 2008.

### Japanese

* 青江 順一. ダブル配列による高速ディジタル検索アルゴリズム. **電子情報通信学会論文誌**, Vol. J71--D, No. 9, pp. 1592-1600, 1988.
* 青江 順一. 自然言語辞書の検索---ダブル配列による高速ディジタル検索アルゴリズム. **bit**, Vol. 21, No. 6, pp. 776-784, 1989.
* 青江 順一. キー検索技法：IV.トライとその応用. **情報処理**, Vol. 34, No. 2, pp 244-251, 1993.
* 森田 和宏, 泓田 正雄, 大野 将樹, 青江 順一. ダブル配列における動的更新の効率化アルゴリズム. **情報処理学会論文誌**, Vol. 42, No. 9, pp. 2229-2238, 2001.
* 大野 将樹, 森田 和宏, 泓田 正雄, 青江 順一. ダブル配列による自然言語辞書の高速更新法. **言語処理学会第11回年次大会発表論文集**, pp. 745-748, 2005.
* 矢田 晋, 森田 和宏, 泓田 正雄, 平石 亘, 青江 順一. ダブル配列におけるキャッシュの効率化. **第5回情報科学技術フォーラム（FIT2006）**, No. LD--008, pp. 71-72, 2006.
