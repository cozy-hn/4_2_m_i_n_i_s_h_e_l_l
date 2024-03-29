# MINISHELL
<img width="261" alt="Screen Shot 2024-03-05 at 9 11 07 PM" src="https://github.com/jonique98/spring-react/assets/104954561/b9058650-6015-470f-a644-3b4bb118b518">

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
<img src="https://github.com/jonique98/spring-react/assets/104954561/f337961f-795c-4b76-9bca-a2dadda1720c">

### EBNF for recursive descent parser
```
- <pipe> ::= <group> “ | ” <group> |  <group> “|” <pipe>
- <group> ::= <cmd> | <redir> <cmd>
- <cmd> ::= <ex_cmd> | <cmd> <option>
- <redir> ::= <redirection> | <redir> <redirection>
- <redirection> ::= “<” <file> | “>” <file> | “>>” <file> | “<<” <limiter>
```

## Tree with commands
<img width="903" alt="Screen Shot 2024-03-05 at 9 26 46 PM" src="https://github.com/cozy-hn/4_2_m_i_n_i_s_h_e_l_l/assets/104954561/2168046a-1e0a-4f72-b6b5-8b1f30d0cf13">
<br>
<br>
<img width="611" alt="Screen Shot 2024-03-05 at 9 25 37 PM" src="https://github.com/cozy-hn/4_2_m_i_n_i_s_h_e_l_l/assets/104954561/10ecc07c-8319-4863-b292-f970b25f495d">
<br>
<br>
<img width="526" alt="Screen Shot 2024-03-05 at 9 23 25 PM" src="https://github.com/cozy-hn/4_2_m_i_n_i_s_h_e_l_l/assets/104954561/f7d056e1-e1c5-4d2f-9c41-1ed2cb80c2fa">


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

<img width="1298" alt="Screen Shot 2024-03-05 at 9 05 43 PM" src="https://github.com/jonique98/spring-react/assets/104954561/d8081710-e28f-4756-9709-d70d2198dcf3">
<br>
<br>

<img width="730" alt="Screen Shot 2024-03-05 at 9 05 17 PM" src="https://github.com/jonique98/spring-react/assets/104954561/588043bf-f975-45d0-b70d-233e641ad53c">
<br>
<br>

<img width="536" alt="Screen Shot 2024-03-05 at 9 06 55 PM" src="https://github.com/jonique98/spring-react/assets/104954561/8f23e286-743d-491d-9f9d-d68ce8ece992">
<br>
<br>

<img width="632" alt="Screen Shot 2024-03-05 at 9 06 12 PM" src="https://github.com/jonique98/spring-react/assets/104954561/5cb72e6b-e993-4c88-b17d-965f9e7c43ab">







