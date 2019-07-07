# stackについて

![](./stack.jpg)

- result.txtの結果を解釈すると図のようになる。
- スタックはこの図では下位アドレスが上で上位アドレスが下なことに注意。
- 変数を書いた順番通りにスタックに積まれるとは限らない。きちんとアセンブリを確認する。
- 上位(0xFFFFFFFF)側から、p, top, argc, argvの順に積まれる。
- 先頭のアドレスを指すので図のようになる


# open
```
fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
```
- openは成功すると0以上、失敗すると-1を返す。
- 最初の引数はファイル名、第二引数はすこし複雑になっている
- `O_CREAT` 新規に作成
- ファイルアクセスモード: `O_RDONLY, O_WRONLY, O_RDWR`それぞれ、読み込み、書き込み、両方。これは単に数字が割り当てられてるだけなので、`O_RDONLY || O_WRONLY != O_RDWR`であることに注意
- `O_TRUNC` すでに存在し通常ファイルである
- `S_xxx`は実行許可があるか確かめるやつらしい(chmodと同じ概念)
- fdは、ファイルディスクリプタ(key-valueのkeyを返してくれている。)
- dprintfはファイルディスクリプタで一意にファイルを指定できる。
- 参考 https://linuxjm.osdn.jp/html/LDP_man-pages/man2/open.2.html

# file discripterとは
- https://mrsekut.site/?p=3048 参考になる
- プロセスごとにファイルディスクリプタテーブルが作られる。
- 作成時に0: 標準入力、1: 標準出力、2: 標準エラー出力で埋まる。
- ファイルをオープンする→3から順番にC言語のintを割り振る
- この数字がfile descripterで、key-valueのkeyがint型の数字、valueがファイルの実体とつなぐ。
- つなぎ方は、数字→グローバルファイルテーブル→inodeテーブル(ここにファイルの属性や場所の情報がある)

# read/write
- dprintfと同様、ファイルディスクリプタと*buf, countを受け取り読み込み/記述する
- read: fd -> buf
- write: buf -> fd
- の違いしかない。

# callocによるヒープ領域への確保
- ファイルサイズがでかくなることに備えてヒープ領域に割当→なぜ？おそらく、スタック領域はpushとpopしかできないので、ヒープに比べてデータを組み替えることが難しいことなのかなぁ。あと、動的にサイズを設定できるのはヒープの強み。
- 参考 https://qiita.com/kackytw/items/256df46d86cfc97b5fa8
```
fd: 3 sz: 2
a
```
- fdは3。サイズは、aとヌル文字合わせて2
- null文字があると、printfで出力可能になるらしい
- printfでは、ヌルバイトが出てくるまで出力される。 ref. https://linuxjm.osdn.jp/html/LDP_man-pages/man3/printf.3.html
- そのため、 `buf+'\0'+'a'` みたいなやつはaが無視される。サイズにも現れない。→オーバーフローの可能性(ヒープ？)あるかも

# lseek
```
read(3, buf, 5)
5 bytes
abcde

lseek(3, 2, SEEK_CUR) => 7
read(3, buf, 5) => 5
34567

lseek(3, 0, SEEK_SET) => 0
read(3, buf, 5) => 5
abcde

lseek(3, -10, SEEK_END) => 5
read(3, buf, 5) => 5
12345

```
- CUR現在の位置にoffsetを足す。5+2で7になる
- SETはファイルオフセット。0なので最初から読み込み
- ENDは最後から。ここはマイナスを指定。pythonの`a[-2:]`みたいな感じ