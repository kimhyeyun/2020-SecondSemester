# 2020-SecondSemester
- 컴퓨터보안
  1. 1차 과제 : steganography 구현
    -> original.bmp 파일에 txt를 인코딩 / 디코딩
        encoding : .bmp 파일에서 EOF 이후 부분이 파일에 큰 영향을 주지않는 점을 이용
        fseek 함수를 이용하여 original.bmp 파일의 EOF로 이동하여 '*'를 넣어 마지막임을 표시한 후, TXT를 삽입
        decoding : 마찬가지로 fseek함수를 이용해 마지막 부분으로 이동하여 stack을 사용해 마지막에서 부터 '*' 까지 읽어욤
   2. 2차 과제 : miller-Rabin 구현
    -> miller-Rabin.py 속 test 함수 구현 :  n-1 의 2^t*u 형태를 구해주고 RSA test와 Fermat test로 prime number 인지 아닌지 검사.
