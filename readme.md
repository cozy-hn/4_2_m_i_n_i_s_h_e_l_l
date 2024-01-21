- [ ] echo '$PWD' $PWD로 잘 보내는데 echo builtin문제로 예상
- [ ] exit시 segfault
executor 넘어가고 falut가 나는데, 확인바람, 너쪽에서 문제 없으면 나가기직전에 터미널 설정 되돌려야 하는데
```
tcsetattr(STDIN_FILENO, TCSANOW, &term);
```
이부분에서 segfault가 나는듯함. 확인바람
- [x] executor에서 leak남 -> arg free 해결
- [ ] "" '' minishell: /usr/local/bin/: Permission denied 뜨는데 찾았다 치고 /usr/local/bin/실행시키는 듯함 수정 요망
- [ ] echo에서 leak나는것 같은데 확인 부탁