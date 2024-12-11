# SimpleDiskInfo
* 디스크의 S.M.A.R.T. 검사를 통해 얻은 데이터 중 디스크의 수명과 연관된 특성들을 통해 디스크의 상태를 알 수 있는 검사 도구 입니다.

## Prerequisites
* 본 프로그램은 [CrystalDiskInfo](https://github.com/hiyohiyo/CrystalDiskInfo)를 통해 얻은 결과를 바탕으로 진행하므로, CrystalDiskInfo를 최소 1번 이상 실행하지 않으면 __**검사를 실시 할 수 없습니다.**__
* 위 프로그램에서 어떤 속성의 원시값(RAW Value)가 오르는 이벤트 로그가 발생하면 디스크의 관련 속성 정보가 갱신됩니다.

## Features
### Check Disk Status
* 디스크의 S.M.A.R.T. 속성들을 불러오고 각 원시값에 따른 디스크의 상태를 보여줍니다.

### Set Threshold Value
* 검사하는 주요 속성들의 임계값(Threshold)을 설정합니다.
* 모델에 따라 임계값이 다르므로 사용하는 디스크의 임계값을 임의로 설정해주세요.
* HDD는 05, C4, C5, C6을 검사하고, SSD는 LIFE의 값만 검사합니다.

## Scanning Attributes
|ID|Attribute|Threshold(Initial)|
|--|---------|------------------|
|05|Reallocated Sectors Count|0|
|C4|Reallocation Event Count|0|
|C5|Current Pending Sector Count|0|
|C6|UncorrectableSectorCount|0|
|FF|Remaining LIFE (for SSD)|10|

## Disk Status
* Caution과 Bad의 조건은 제가 임의로 설정한 것이며, 실제 Disk Health랑 다를 수 있습니다.

|Status|Condition|
|------|---------|
|Good|모든 원시값이 0|
|Caution|원시값이 0보다 크고, 임계값을 넘어간 속성이 있음|
|Bad|모든 속성의 원시값이 임계값을 넘어감|
|Unknown|오류(디스크 폴더를 읽지 못함)|

## Demo Screenshot
<img width="70%" src="https://github.com/user-attachments/assets/fc901f27-4a8e-4889-9dc9-ddc51f40baac">
<img width="70%" src="https://github.com/user-attachments/assets/b4787f47-5e17-4aa2-89ec-46edaec0d019">
<img width="70%" src="https://github.com/user-attachments/assets/2abf28f9-0531-466f-9dc2-e43ac92d1868">

## References
* [CrystalDiskInfo](https://github.com/hiyohiyo/CrystalDiskInfo)

* [근둥이의 블로그 - [C/C++] 콘솔게임 프로그래밍](https://geundung.dev/17?category=699626)

* [Choilngon - CSVReader](https://github.com/ChoiIngon/blog/tree/master/216/CSVReader_cpp)

* [TCHARToString](dhkvmf88.tistory.com/56)

* [디렉토리 폴더 파일 목록 탐색 검색](https://nauco.tistory.com/5)

## License
This project is licensed under the MIT License