# MyParser

c言語ベースの自作構文解析器です。
- 言語：c++14~

## 各ファイルについて
- ParserToken.h
	- 字句クラスの定義（文字列と、その文字列がどういう種類のものか）
- Parser.h
	- 解析された字句をもとに構文を解析し、木構造にして返す
- Lexer.h
	- 字句解析を行う
- TreeNode.h
	- 構文解析木のノードの定義

## 詳しい仕様
- 四則演算、余りの計算が可能
	- 数値はdouble型で記憶
- 変数の定義はまだ

## 参考文献
- https://joho-ka.mints.ne.jp/create-abstract-syntax-tree?doing_wp_cron=1607037495.0281510353088378906250
	- 構文解析をして抽象構文木を作ってみる
	- 最終閲覧日 2021/03/10
- https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm
	- The syntax of C in Backus-Naur Form
	- 最終閲覧日 2021/03/10