# 八五式電子観測儀 (Type-85-Electronic-Observer)

Qt6で作成されたクロスプラットフォームな艦これ補助専ブラ

## 現在のToDo

- [X] Create CEF instance and try accessing game's web page
- [ ] Try capturing API and Display as a dock widget
- [ ] Extract and Format API response into usable state

## Road Map

- 0.0.1 ~ 0.1.0: Browser, Base Module
- 0.1.1 ~ 0.2.0: Proxy Server(`observer-qt`), `api_start2/getData` dumping
- 0.2.1 ~ 0.3.0: API Deciphering (`analyzer` library)
- 0.3.1 ~ 0.9.0: Module Development(`ui`)
- 0.9.1 ~ 1.0.0: Finalize
- ~ Rolling Release: Following updates, modifing analyzer, bug fixes

## 動機

* [提督](https://github.com/kenryuS)が重度のLinux中毒者であること
* [七四式電子観測儀](https://github.com/dais-k/ElectronicObserver)がWindows専用(WinForms使用)だったこと
* 自分のスキルを試めしたかった

## 機能(予定)

各機能はQDockWidgetを使用してアプリ内で自由にタイリング、ウィンドウ化させることができます。

* 内蔵ブラウザー(スクリーンショット、ズーム、ミュート)
* 艦隊情報
    * 個艦
    * 艦隊一覧
* 入渠状況
* 工廠状況
* 羅針盤
* 海域情報
* 戦闘情報
* 任務状況
* 通知機能
* 記録

## 使用ライブラリー(予定)

* [Qt6](https://doc.qt.io/qt-6/index.html) - UIフレームワーク - [GPLv3]()
* [Qt WebEngine](https://doc.qt.io/qt-6/qtwebview-index.html) - Chromiumベースのウェブエンジン [LGPL-3.0]()
* [json](https://github.com/nlohmann/json) - JSONデータの読み書き、ヘッダーオンリーライブラリー - [MIT license]()
* [検討中]() - http プロキシ、通信キャプチャー - [未定]()

## ダウンロード

* Windows            : (未定)
* Linux              : (未定)
* MacOSX             : (未定)

## ビルドガイド

```bash
$ git clone https://github.com/kenryuS/Type-85-Electronic-Observer.git EO
$ cd EO
$ nix develop // Nix が使える場合
$ mkdir build
$ cd build
$ cmake ..
$ cmake .. -DCMAKE_BUILD_TYPE=Debug // デバッグビルドしたい時
$ make
$ make install
```

## 諸注意

現在このプログラムは開発段階にあり、すべての機能が実装されておらず、予期せぬ動作で損害を受けても開発者は***一切の責任を負いません***。
