## [팀 프로젝트]
<h4>날짜: 2020.05.18 | 작성자: 김주연 | Version: 1.0 </h4>
<hr>
<h3> 1. 요구사항 분석 (Requirement Analysis) </h3>
<h4>- 데이터 입력, 정렬 후 출력, 파일 출력</h4>
<br>
<h3> 2. 구조 설계 (Structure Design) </h3>
<h4> 1) 첫 번째 콘솔 입력창: 메뉴 생성 (입력/출력/파일출력/파일입력)</h4>

<h4> 2) 구조체 선언 및 생성 </h4>
<h5>- teamList: id(번호), team(팀 이름), company(회사)</h5><br>

<h4> 3) 기능(함수) 선언 및 정의 </h4>
<h5>- menu: 메뉴 → 사용자의 선택 </h5> 
<h5>- input: 데이터 입력</h5> 
<h5>- sortingSelect: 정렬 선택 → 사용자의 선택</h5> 
<h5>- bubbleSorting: 데이터 정렬</h5> 
<h5>- printingList: 데이터 출력</h5>
<h5>- fileWriting: 파일 쓰기</h5> 
<h5>- fileReading: 파일 읽기</h5><br>

<h4> 4) teamF.h : 구조체 선언, 함수 선언 </h4>
<h4> 5) teamF.c : 함수 정의, include teamF.h </h4>
<h4> 6) main.c : teamF.c 함수 호출, 전체 흐름 알고리즘 </h4>
<br>
<hr>
<br>
<h3> 3. 입력/출력 데이터 정의 (Data Structure Design) </h3>
<h4> - 데이터 종류: 번호(id), 팀 이름(team), 회사(company) </h4>
<h4> - 입력: 기본 입력은 아래 표와 같다. </h4>
<br>
<table>
 <tr>
  <th>번호</th>
  <th>팀 이름</th> 
  <th>회사</th>
  </tr>
 
 <tr>
  <td>1</td>
  <td>horangnavi(호랑나비)</td>
  <td>navilab(나비랩)</td>
 </tr>
 
  <tr>
  <td>2</td>
  <td>machinegun(머신건)</td>
  <td>5works</td>
 </tr>
 
  <tr>
  <td>3</td>
  <td>megaton(메가톤)</td>
  <td>megazone(메가존)</td>
 </tr>
 
   <tr>
  <td>4</td>
  <td>dd</td>
  <td>vitec(VITEC)</td>
 </tr>
 
  <tr>
  <td>5</td>
  <td>banana</td>
  <td>monkeysoft(몽키소프트)</td>
 </tr>
 
  <tr>
  <td>6</td>
  <td>park123(박123)</td>
  <td>nurdbana(너드바나)</td>
 </tr>
   </table>

<br>
<hr>
<h3> 4. 알고리즘 설계 및 구현 (Algorithm Design and Implementation) </h3>
<ul>
   <li>
<h4>메뉴 함수 알고리즘 (menu)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/menu_Function.png" width="30%" height="20%">
  <li>
<h4>데이터 입력 함수 알고리즘 (input)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/input_Function.png" width="30%" height="20%">
  <li>
<h4>정렬 선택 함수 알고리즘 (sortingSelect)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/sortingSelect_Function.png" width="20%" height="20%">
<li>
<h4>정렬 함수 알고리즘: 버블정렬 (bubbleSorting)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/bubbleSorting_Function.png" width="100%" height="70%">
 <li>
<h4>출력 함수 알고리즘 (printingList)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/printingList_Function.png" width="100%" height="70%">
 <li>
 <h4>파일 쓰기 및 저장 함수 알고리즘 (fileWriting)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/fileWriting_Function.png" width="100%" height="70%">
 <li>
<h4>파일 읽기 함수 알고리즘 (fileReading)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/fileReading_Function.png" width="100%" height="70%">
 </ul>
<br>

<br>
<hr>
<h3> 5. 코딩 및 테스트 (Coding and Test) </h3>
<ul>
 <li>
<h4><a href="https://github.com/ksa-banana/C_Language/tree/master/TeamProject_20200518/version_01">프로젝트</a></h4>
 </li>
 <li><h4>첫 번째 출력화면</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/01.PNG" width="50%" height="50%">
  <li><h4>입력 선택, 데이터 입력</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/02.PNG" width="50%" height="50%">
  <li><h4>정렬 선택, 정렬 기준 </h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/03.PNG" width="50%" height="50%">
  <li><h4>정렬 기준 선택, 오름차순 선택</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/04.PNG" width="100%" height="100%">
  <li><h4>id를 기준으로 오름차순 선택</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/05.PNG" width="100%" height="100%">
   <li><h4>id를 기준으로 내림차순 선택</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/06.PNG" width="100%" height="100%">
 <li><h4>팀 이름을 기준으로 오름차순 선택</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/07.PNG" width="100%" height="100%">
  <li><h4>팀 이름을 기준으로 내림차순 선택</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/08.PNG" width="100%" height="100%">
 <li><h4>회사 이름을 기준으로 오름차순 선택</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/09.PNG" width="100%" height="100%">
  <li><h4>회사 이름을 기준으로 내림차순 선택</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/09.PNG" width="100%" height="100%">
   <li><h4>파일 출력 선택</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/10.PNG" width="50%" height="50%">
    <li><h4>파일 출력 결과</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/12.PNG" width="100%" height="100%">
 <li><h4>파일 입력 선택, 결과</h4></li>
 <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200518/image/11.PNG" width="50%" height="50%">
 </li>
</ul>
