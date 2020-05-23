## [팀 프로젝트]
<h4>날짜: 2020.05.20 | 작성자: 강나래 | Version: 1.1 </h4>
<hr>
<h3> 1. 요구사항 분석 (Requirement Analysis) </h3>
<h4>- 데이터 파일 읽고 구조체에 저장, 데이터 검색, 검색 결과 파일 출력</h4>
<br>
<h3> 2. 구조 설계 (Structure Design)</h3>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/systemStructure.png" width="20%" height="20%">
<h4> 1) 첫 번째 콘솔 입력창: 메뉴 생성 (조장 검색/기업 검색/이름 검색/이메일 검색/학교 검색/전공 검색)</h4>

<h4> 2) 구조체 선언 및 생성 </h4>
<h5>- studentList: leader(조장 여부), company(회사), name(이름), email(이메일), school(학교), major(전공)</h5><br>
<table>
<tr>
 <th>조장 여부</th>
 <th>회사</th>
 <th>이름</th>
 <th>이메일</th>
 <th>학교</th>
 <th>전공</th>
</tr>
</table>

<h4> 3) 기능(함수) </h4>
<h5>- getFileSize: 파일 라인 크기 반환 </h5>
<h5>- menu: 메뉴 → 사용자의 선택 </h5>
<h5>- fileReading: 파일 읽기 </h5>
<h5>- retToken: 토큰으로 데이터 자르기 </h5>
<h5>- inputData: 정제된 데이터 구조체에 저장 </h5>
<h5>- searchingLeader: 조장 컬럼 검색 </h5>
<h5>- searchingCompany: 기업 컬럼 검색 </h5>
<h5>- searchingName: 이름 컬럼 검색 </h5>
<h5>- searchingEmail: 이메일 컬럼 검색 </h5>
<h5>- searchingSchool: 학교 컬럼 검색 </h5>
<h5>- searchingMajor: 전공 컬럼 검색 </h5>
<h5>- searchingResultPrintf: 검색 결과 출력 </h5>
<h5>- fileWrithing: 파일 출력 </h5><br>

<h4> 4) studnetP.h : 구조체 선언, 함수 선언  </h4>
<h4> 5) studentP.c : 함수 정의, include studnetP.h </h4>
<h4> 6) main.c : studentP.c 함수 호출, 전체 흐름 알고리즘 </h4>
<br>
<hr>
<br>
<h3> 3. 입력/출력 데이터 정의 (Data Structure Design) </h3>
<h4> - 데이터 종류: leader(조장 여부), company(회사), name(이름), email(이메일), school(학교), major(전공), time(시간) </h4> 
<h4> - 입력: 주어진 엑셀 파일 데이터는 아래 표와 같다.(dummy data) </h4> 
<br>
<table>
 <tr>
  <th>조장 여부</th>
  <th>배정 기업</th> 
  <th>이름</th>
  <th>이메일</th>
  <th>학교</th>
  <th>전공</th>
  </tr>
 
 <tr>
  <td>조장</td>
  <td>A기업</td>
  <td>김**</td>
  <td>***@email.com</td>
  <td>**대학교</td>
  <td>컴퓨터공학</td> 
 </tr>
  <tr>
  <td></td>
  <td>A기업</td>
  <td>최**</td>
  <td>***@email.com</td>
  <td>**대학교</td>
  <td>화학공학</td> 
 </tr>
 
 <tr>
  <td>조장</td>
  <td>B기업</td>
  <td>이**</td>
  <td>***@email.com</td>
  <td>**대학교</td>
  <td>소프트웨어공학</td> 
 </tr>
 
  <tr>
  <td></td>
  <td>B기업</td>
  <td>임**</td>
  <td>***@email.com</td>
  <td>**대학교</td>
  <td>전자공학</td> 
 </tr>
 
 <tr>
  <td>조장</td>
  <td>C기업</td>
  <td>이**</td>
  <td>***@email.com</td>
  <td>**대학교</td>
  <td>기계공학</td> 
 </tr>
  <tr>
  <td></td>
  <td>C기업</td>
  <td>박**</td>
  <td>***@email.com</td>
  <td>**대학교</td>
  <td>정보통신공학</td> 
 </tr>
  <tr>
  <td></td>
  <td>C기업</td>
  <td>이**</td>
  <td>***@email.com</td>
  <td>**대학교</td>
  <td>생명공학</td> 
 </tr>
  <tr>
  <td></td>
  <td>C기업</td>
  <td>고**</td>
  <td>***@email.com</td>
  <td>**대학교</td>
  <td>컴퓨터시스템공학</td> 
 </tr>
 
 <tr>
  <td>조장</td>
  <td>D기업</td>
  <td>강**</td>
  <td>***@email.com</td>
  <td>**대학교</td>
  <td>산업공학</td> 
 </tr>
 
  <tr>
  <td></td>
  <td>D기업</td>
  <td>박**</td>
  <td>***@email.com</td>
  <td>**대학교</td>
  <td>항공우주</td> 
 </tr>
   </table>

<br>
<hr>
<h3> 4. 알고리즘 설계 및 구현 (Algorithm Design and Implementation) </h3>
<ul>
<li>
<h4>메인 함수 알고리즘 (main)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/main_Function.png" width="20%" height="20%">
  <li>
<h4>메뉴 함수 알고리즘 (menu)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/menu_Function.png" width="20%" height="20%">
  <li>
<h4>엑셀 파일 읽기 함수 알고리즘 (fileReading)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/fileReading_Function.png" width="20%" height="20%">
 <li>
<h4>토큰 함수 알고리즘 (retToken)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/retToken_Function.png" width="30%" height="30%">
 <li>
<h4>데이터 저장 함수 알고리즘 (inputData)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/inputData.png" width="30%" height="30%">
  <li>
<h4>데이터 검색 함수 알고리즘: 조장 검색 (searchingLeader)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingLeader_Function.png" width="30%" height="30%">
 <li>
<h4>데이터 검색 함수 알고리즘: 기업 검색 (searchingCompany)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingCompany_Function.png" width="30%" height="30%">
  <li>
<h4>데이터 검색 함수 알고리즘: 이름 검색 (searchingName)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingName_Function.png" width="30%" height="30%">
   <li>
<h4>데이터 검색 함수 알고리즘: 이메일 검색 (searchingEmail)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingEmail_Function.png" width="30%" height="30%">
    <li>
<h4>데이터 검색 함수 알고리즘: 학교 검색 (searchingSchool)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingSchool_Function.png" width="30%" height="30%">
  <li>
<h4>데이터 검색 함수 알고리즘: 전공 검색 (serachingMajor)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingMajor_Function.png" width="30%" height="30%">
 <li>
<h4>검색 기록 파일 쓰기 함수 알고리즘 (logFileWrithing)</h4>
 </li>
<img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/fileWriting_Function.png" width="30%" height="30%">
 </ul>
<br>

<br>
<hr>
<h3> 5. 코딩 및 테스트 (Coding and Test) </h3>
<ul>
 <li><h4>메뉴 출력화면</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/menu_view.PNG" width="50%" height="50%">
 <li><h4>조장 검색 출력화면</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingLeader_view.PNG" width="50%" height="50%">
 <li><h4>회사 검색 출력화면</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingCompany_view.PNG" width="50%" height="50%">
 <li><h4>이름 검색 출력화면</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingName_view.PNG" width="50%" height="50%">
 <li><h4>Email 검색 출력화면</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingEmail_view.PNG" width="50%" height="50%">
 <li><h4>학교 검색 출력화면</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingSchool_view.PNG" width="50%" height="50%">
 <li><h4>전공 검색 출력화면</h4></li>
  <img src="https://github.com/ksa-banana/C_Language/blob/master/TeamProject_20200519/image/searchingMajor_view.PNG" width="50%" height="50%">
 </ul>
