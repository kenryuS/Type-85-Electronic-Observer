# KC API Analyzer

別のフレームワークに移植しやすいように、API解析に焦点を置いたライブラリ。

基本的には入力にサーバーで抽出したJSONとAPIパスを、出力に扱いやすく整形されたJSONを返すようになっている。

なお、JSONは他のフレームワーク等の互換性確保のため、引数・戻り値すべて`std::String`として扱う。
ライブラリ内部ではヘッダーオンリーの[nlohmann's JSON](https://github.com/nlohmann/json)を使用している。

