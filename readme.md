- [x] echo '$PWD' $PWD로 잘 보내는데 echo builtin문제로 예상 - 종료 코드($?) 관련 조건문 수정 후 해결 - 해결 완 arg프리해줌
- [x] exit시 segfault executor 넘어가고 falut가 나는데, 확인바람, 너쪽에서 문제 없으면 나가기직전에 터미널 설정 되돌려야 하는데 -> 인덱스에 잘못된 상수가 하드코딩 돼있었음 수정 후 해결
이부분에서 segfault가 나는듯함. 확인바람
- [x] executor에서 leak남 -> arg free 해결
- [x] "" '' minishell: /usr/local/bin/: Permission denied 뜨는데 찾았다 치고 /usr/local/bin/실행시키는 듯함 수정 요망 
        -> 먼말인지 모르겠는데 암튼 한번 해보셈 해결 됐을듯
        -ㄴㄴ 안됨 그냥 미니쉘에 "" 치면 무슨말인지 알듯
        - 이해했음 해결 완
- [x] echo에서 leak나는것 같은데 확인 부탁 -> echo에서는 할당이 없어서 적어도 leak은 없을 것으로 예상
- [x] 없는 환경 변수 (ex -> $test, $qwer) 에서 segfault =>수정 완
- [x] gnl 가져와야함 -> readline으로 대체 가능 -> readline은 leak날수도
- [x] minishell$ misdaf => minishell: misdaf$?: command not found: minishell$  줄바꿈 추가좀
- [x] strncmp 길이 비교 문자열 +1 까지해야하는데 전체 변경좀 내가 바꾸다 바꿀게 넘 많아서 포기 ex) echoooooooooo hi 도 나욤
- [x] heredoc이면 임시파일 지워야하는데 코드 확인필요 -> tmp에 써지는건 확인 -> handle_heredoc에서 지워줌
- [x] $PWD, $OLDPWD : cd .. 시  수정 요망 
        -> 발견 굿
- [x] 오류나고 $? 확인하면 exit code가 0으로 나옴
- [x] heredoc -> heredoc1 -> heredoc12 -> heredoc123이렇게 생기는데 의도에 맞는지 확인
        -> 수정함 (heredoc1 -> heredoc2 -> heredoc3)

- [ ] 폴더 현재폴더로 ./.tmp에 넣고 싶은데 폴더 있나 확인하고 없으면 만드는 코드 추가 요망

- [ ] cat만 치고 ctrl + c 누르면 minishell$ 두번 뜸
        -> 이건 모르겠네요..
- [ ] export a=b && echo $a : 수정필요
        -> expansion 시점 변경

- [ ] first middle last에서 fd_in fd_out 존재 시 부모 프로세스에서 fd 닫아주기 (수민)
- [ ] redirection 에서 파일명 leak (ex, >> a 하면 "a" leak)

## handle_heredoc (heredoc.c)
```
heredoc 닫아주는 함수
인자로 arg 받음 일단은 arg->next 순회 안하고 인자로 들어온 arg만 해줌

void	handle_heredoc(t_arg *arg)
{
	t_lst	*lst;

	lst = arg->lst;
	while (lst)
	{
                //lst->in_type 초기화 해줘야함
                //lst 순회하면서 heredoc이면 in_name을 삭제(unlink) 해줌
		if (lst->in_type == T_L_D_REDIR)
		{
			if (access(lst->fd_in_name, F_OK) == 0)
				unlink(lst->fd_in_name);
		}
		lst = lst->next;
	}
}
```




## heredoc.c
```
void	heredoc(t_lst *lst);

lst를 인자로 받아서 임시 파일(heredoc)생성
리미터(ex. << limiter)까지 입력받은 후(포함 x)
임시파일 fd닫고 lst->fd_in_name 초기화 해줌

**함수 실행 전에 lst->cmd[0]을 limiter로 초기화 시켜줘야 함(<< "limiter")**

gnl없어서 readline으로 테스트 했고, 적힌 동작까지는 test 성공 (에러는 아직 모름)
heredoc처리 전까지는 파이프 전후 파일 안열리는거 확인 즉 순서 신경쓸 필요 없음
그래서, 예상하기로는 fd 열어줄 때 heredoc일 시 이 함수 실행하면 될거임 되길 바람
임시 파일 삭제는 내쪽에서 처리함

예상 이슈
heredoc 인자로 받고있을 때 시그널로 종료 시 임시파일 삭제해야할듯
```

### 임시 버전
```
void	heredoc(t_lst *lst)
{
    int		fd;
    char	*line;
    char    *name;
    int     i;

    //heredoc이름 중복되지 않게 생성
    i = 0;
    name = ft_strdup("/tmp/heredoc");
    while (access(name, F_OK) == 0)
    {
        free(name);
        name = ft_strjoin("/tmp/heredoc", ft_itoa(++i));
    }
    fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);

    //표준입력으로 입력 받음
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(0);
        //리미터를 입력받으면 반복문 break
        if (ft_strncmp(line, lst->cmd[0], ft_strlen(lst->cmd[0])) == 0)
        {
            free(line);
            break ;
        }
        ft_putendl_fd(line, fd);
        free(line);
    }
    //lst->fd_in_name 초기화
    lst->fd_in_name = name;
    //fd close
    close(fd);
}
```