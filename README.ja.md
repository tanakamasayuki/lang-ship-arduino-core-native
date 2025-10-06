# lang-ship Arduino ネイティブ SDL2 プラットフォーム

このリポジトリは `lang-ship:native` Arduino Boards Manager プラットフォームを提供します。M5Stack 互換スケッチをデスクトップ上の SDL2 環境で実行できるため、実機を書き換えずに高速な反復開発が可能です。

## 特長
- ESP32 版 M5Stack ボード定義を踏襲しつつ、SDL2 ネイティブ実行をターゲットにします。
- ネイティブ版と実機版で同じスケッチコードをそのまま共有できます。
- 基本は M5Stack ボードで採用されている M5Unified API と互換です。M5Unified が内部で利用する描画エンジン M5GFX に依存し、M5GFX は同作者の LovyanGFX と機能がほぼ共通でネームスペースや対応パネルが異なるだけなので、ネームスペースを考慮すれば LovyanGFX 互換としても扱えます。
- SDL2／clang／gcc などのツールチェーンはシステムにインストール済みのものを利用します（現時点でバンドルなし）。

## 前提条件
- Arduino CLI または Arduino IDE（2.x 推奨）。
- SDL2 開発ライブラリがシステムパス上で利用可能であること。
- C/C++ ツールチェーン（clang/gcc など）がコマンドラインから実行可能であること。

## 使い始めるには
1. このリポジトリを Arduino CLI の設定ディレクトリまたは Vendor Index の作業領域にクローンします。
2. `platform.txt` やボード定義ファイルが整備され次第（初回リリース予定）、Boards Manager 用パッケージを生成します。
3. Arduino CLI または Arduino IDE からパッケージをインストールし、`lang-ship:native` ターゲットを選択して通常どおりビルド／アップロードします。

> **ヒント:** ツールチェーンが標準パスに存在しない場合は、`sketch.yaml` の `--build-property` で上書き指定できます。
>
> ```bash
> arduino-cli compile \
>   --fqbn lang-ship:native:m5stack_core \
>   --build-property compiler.path="C:/msys64/ucrt64/bin/"
> ```

## バージョン管理
- セマンティックバージョン（例: `v1.0.0`）のタグを打ってリリースします。
- 自動化スクリプトによって `platform.txt` の `version=` が最新タグに同期されます。
- `script/make_dist.sh` を実行すると、パッケージ化前にバージョン文字列が更新されます。

## ロードマップ
- 初回リリースで M5Stack ボード向けの `platform.txt`、コア、バリアント定義を追加します。
- ビルド検証やパッケージ生成を自動化するヘルパースクリプトを整備します。
- SDL2／clang／gcc などのツールを同梱するオプションを検討します。

## コントリビュート
Issue や Pull Request を歓迎します。`README.md` と `README.ja.md` の内容が常に同期されるよう注意してください。

## ライセンス
MIT License に基づき公開しています。詳細は `LICENSE` を参照してください。

