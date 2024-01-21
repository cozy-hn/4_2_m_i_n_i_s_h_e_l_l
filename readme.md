- [ ] echo '$PWD' -니탓
- [ ] exit시 segfault
executor 넘어가고 falut가 나는데, 확인바람, 너쪽에서 문제 없으면 나가기직전에 터미널 설정 되돌려야 하는데
```
tcsetattr(STDIN_FILENO, TCSANOW, &term);
```
이부분에서 segfault가 나는듯함. 확인바람
