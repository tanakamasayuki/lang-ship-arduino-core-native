# lang-ship Arduino ネイティブ SDL2 プラットフォーム

このリポジトリは `lang-ship:native` Arduino Boards Manager プラットフォームを提供します。M5Stack 互換スケッチをデスクトップ上の SDL2 環境で実行できるため、実機を書き換えずに高速な反復開発が可能です。

## 特長
- ESP32 版 M5Stack ボード定義を踏襲しつつ、SDL2 ネイティブ実行をターゲットにします。
- ネイティブ版と実機版で同じスケッチコードをそのまま共有できます。
- 基本は M5Stack ボードで採用されている M5Unified API と互換です。M5Unified が内部で利用する描画エンジン M5GFX に依存し、M5GFX は同作者の LovyanGFX と機能がほぼ共通でネームスペースや対応パネルが異なるだけなので、ネームスペースを考慮すれば LovyanGFX 互換としても扱えます。
- SDL2／clang／gcc などのツールチェーンはシステムにインストール済みのものを利用します（現時点でバンドルなし）。
- プレースホルダーのピンマップと SDL2 駆動のメインループを備えた `m5stack_core` ボードプロファイルを初期実装として含みます。

## 使い始めるには
1. このリポジトリを Arduino CLI/IDE が参照するハードウェアディレクトリ（例: `~/Arduino/hardware/lang-ship/native`）にクローンします。
2. Arduino CLI でスケッチをコンパイルします。
   ```bash
   arduino-cli compile \
     --fqbn lang-ship:native:m5stack_core \
     path/to/your/sketch
   ```
3. ビルドフォルダに生成される実行ファイルを起動します（Windows では既定で `.exe` 拡張子になります）。
4. 必要に応じてツールチェーン探索を上書きします。
   ```bash
   arduino-cli compile \
     --fqbn lang-ship:native:m5stack_core \
     --build-property compiler.path="C:/msys64/ucrt64/bin/" \
     --build-property build.exec_ext=.exe \
     path/to/your/sketch
   ```

## ディレクトリ構成
- `platform.txt`: コンパイラ設定、SDL2 リンクフラグ、ビルドレシピを定義します。
- `boards.txt`: 既定のビルドフラグと共に `m5stack_core` SDL2 ターゲットを登録します。
- `cores/native`: タイマ／Serial 出力／SDL2 イベントループを提供する試作 Arduino コア実装です。
- `variants/m5stack_core`: M5Stack プロファイル向けのプレースホルダーピン割り当てとバリアント初期化フックです。

## ツールチェーン上書き
- `compiler.path` は空文字が既定で、システムの `PATH` に依存します。`--build-property compiler.path=...` で任意ディレクトリを指定できます。
- `build.exec_ext` は生成物の拡張子を制御します（`boards.txt` では `.exe` を既定に設定）。POSIX 系 OS で拡張子が不要な場合は上書きしてください。
- SDL2 関連の追加リンカフラグが必要なら `--build-property build.sdl_ldflags="-lSDL2main"` のように渡せます。

## バージョン管理
- セマンティックバージョン（例: `v1.0.0`）のタグを打ってリリースします。
- 自動化スクリプトによって `platform.txt` の `version=` が最新タグに同期されます。
- `script/make_dist.sh` を実行すると、パッケージ化前にバージョン文字列が更新されます。

## 現在の制限
- 周辺機器のエミュレーションは最小限で、GPIO／オーディオ／グラフィックス制御は SDL2 ベースの実装待ちです。
- Serial 入力は `std::cin` を利用した同期読み込みで、ノンブロッキング挙動は未対応です。
- `arduino-cli upload` にはまだ対応していません。現時点では生成された実行ファイルを手動で起動してください。

## ロードマップ
- SDL2 上で M5Unified と LovyanGFX を駆動できるよう `cores/native` を充実させます。
- ビルド検証やパッケージ生成を自動化するヘルパースクリプトを整備します。
- SDL2／clang／gcc などのツールを同梱するオプションを検討します。

## コントリビュート
Issue や Pull Request を歓迎します。`README.md` と `README.ja.md` の内容が常に同期されるよう注意してください。

## ライセンス
MIT License に基づき公開しています。詳細は `LICENSE` を参照してください。



