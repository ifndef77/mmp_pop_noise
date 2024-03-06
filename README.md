# 미유 미니 플러스 팝 노이즈 제거 회로

## 노이즈 발생 및 해결 상황
- 전원 ON시 (완료)
- 전원 버튼으로 전원 OFF시 (완료)
- 슬립모드에서 전원 OFF시 (완료)
- NDS 게임 기동 및 종료시 (해결 불가능)


### 하드웨어 개발환경
- CH32V003J4M6 (SOP8) CPU 사용
- PlatformIO + Arduino 컴파일러
- WCH-Link-E 다운로더



### CH32V003J4M6 핀 연결
[CH32V003 Datasheet](https://www.wch-ic.com/downloads/CH32V003DS0_PDF.html)
- 2 : GND
- 4 : VCC (3V)
- 5 : PWM Signal Input
- 6 : Speaker Mute (이어폰 연결 확인) Output - 10kohm 저항 직렬연결
- 7 : Power Switch Input - 1N4148 다이오드 연결 (전원 OFF시 전원 공급 방지용)

![MMP noise](./photo/image%201.jpeg)