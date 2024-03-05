# MINISHELL

## 과제 목표
- Bash Manual을 참고하여 쉘을 구현한다
- Recursive descent parser
- Inter Process Communication

## Bash Manual
- [Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)

## 구현 기능
- 기본적인 쉘 기능
- Built-in 명령어
- 환경변수
- 상대경로, 절대경로
- 파이프
- 리다이렉션
- 시그널

## flow chart
<img>

### EBNF for recursive descent parser
```
- <pipe> ::= <group> “ | ” <group> |  <group> “|” <pipe>
- <group> ::= <cmd> | <redir> <cmd>
- <cmd> ::= <ex_cmd> | <cmd> <option>
- <redir> ::= <redirection> | <redir> <redirection>
- <redirection> ::= “<” <file> | “>” <file> | “>>” <file> | “<<” <limiter>
```

### Built-in

<details>
<summary>env</summary>
환경 변수 목록을 출력
</details>

<details>
<summary>export</summary>
환경변수를 설정하거나 환경변수 목록을 출력
</details>

<details>
<summary>unset</summary>
환경변수를 삭제
</details>

<details>
<summary>pwd</summary>
현재 디렉토리 출력
</details>

<details>
<summary>cd</summary>
디렉토리 변경
</details>

<details>
<summary>exit</summary>
쉘 종료 (파이프 제외)
</details>

<details>
<summary>echo - n</summary>
문자열 출력, n옵션은 줄바꿈을 하지 않음
</details>


## 실행 방법
```
git clone
make
./minishell
```

## 실행 예시
<img>





