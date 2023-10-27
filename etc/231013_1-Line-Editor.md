### [JAVA] 

```java
import java.util.ArrayList;

class UserSolution {


class cursor{

int loc;                         //1 Line editor 전체 기준 현재 위치(0부터 시작)

int wordid;                      //단어id(단어 위치, 1부터 시작)

int wordloc;                     //단어 내 커서 위치(0부터 시작)


public cursor(int loc,int id,int wloc) {

this.loc = loc;

this.wordid = id;

this.wordloc = wloc;

}

}


cursor C;

ArrayList<String> word;


public void init() {

C = new cursor(0,1,0);            //0번 단어가 더미라서 wordid는 1부터

word = new ArrayList<String>();

String dummy = new String();      //0번 더미 data, word가 비어있으면 word.size()가 에러, isEmpty()로 항상 비교하기보다 배열 1번부터 시작하면 편해서..

word.add(dummy);

}



public char putString(char[] mStr) {

String addword = new String();

char nextword[] = new char[10];      //단어 입력 중 단어를 분리해야하는 경우 다음 단어로 넘길때 사용(mStr이 최대 10개 문자이므로 무조건 10개 미만)

int wordflag = 0;                    //0:소문자 단어 시작 전, 1:소문자로 단어가 시작된 경우, 2:소문자 입력 중 '_'로 이후 단어를 다음 putString으로 넘길 경우

int nextstart = 0;


for(int i=0;i<mStr.length;i++) {

if(mStr[i] == 0) {               //공백 시 입력 종료

break;

}


if(wordflag == 0 && mStr[i] != '_' && mStr[i] != 'R' && mStr[i] !='L' && mStr[i] !='F' && mStr[i]!='B' && mStr[i]!='D') {  

wordflag = 1;                      //소문자 단어 시작

}

else if((wordflag == 1 &&              //소문자 단어 시작 이후 문자를 다음 단어로 넘기는 경우(한번 입력에 단어 id를 복수 부여해야될 case)

((mStr[i-1] == '_' && mStr[i] != '_')||mStr[i] == 'R' || mStr[i] =='L' || mStr[i] =='F' || mStr[i] == 'B' || mStr[i]=='D'))

||wordflag == 2) {

wordflag = 2;

nextword[nextstart] += mStr[i];

nextstart++;

continue;

}


if(mStr[i]=='R') {

i++;

int mv = mStr[i] - '0';


while(mv > 0) {

if(C.wordid == word.size()) {                    //이동 중 마지막까지 가면 끝

break;

}


if(C.wordloc+mv >= word.get(C.wordid).length()) {       //현재 word수를 초과하는 경우

C.loc += word.get(C.wordid).length()-C.wordloc;

mv -= word.get(C.wordid).length()-C.wordloc;


C.wordid++;

C.wordloc = 0;

}

else {                                           //현재 word 내에서 이동 가능한 경우

C.wordloc += mv;

C.loc += mv;

mv = 0;

}

}


continue;

}


if(mStr[i]=='L') {

i++;

int mv = mStr[i] - '0';


while(mv > 0) {

if(C.wordloc-mv < 0) {                            //현재 word 앞으로 이동해야하는 경우

mv -= C.wordloc+1;

C.loc -= (C.wordloc<C.loc?C.wordloc+1:C.loc);   //범위 초과 시 0


if(C.wordid == 1) {                           //현재 word가 맨 앞이었던 경우 

C.wordloc = 0;

break;

}

else {                                        //이전 word의 맨 마지막으로 이동

C.wordid--;

C.wordloc = word.get(C.wordid).length()-1;

}

}

else {                                           //현재 word 내에서 이동 가능한 경우

C.wordloc -= mv;

C.loc -= mv;

mv = 0;

}

}


continue;

}


if(mStr[i]=='F') {

i++;

int mv = mStr[i] - '0';

int cnt = word.get(C.wordid).length() - C.wordloc - 1; //현재 word의 끝지점까지 글자 수


if(word.get(C.wordid).charAt(C.wordloc)=='_') {        //현재 위치값이 '_'로 소문자 시작전인 경우 현재 위치의 문자열을 1회 이동으로 치환

mv--;

}


while(mv > 0) {

if(C.wordid == word.size()-1) {                  //현재 word가 마지막이면 미 이동

break;

}


mv--;

C.wordid++;

cnt += word.get(C.wordid).length();              //이동 총 글자수 합산

}


C.wordloc = word.get(C.wordid).length()-1;           //최종 word의 끝지점으로 위치 이동

C.loc += cnt;                                        //cursor의 현재위치 update


while(word.get(C.wordid).charAt(C.wordloc) == '_') {  //끝지점이 "_"이면 아닌 지점까지 이동

C.loc--;

C.wordloc--;

}


continue;

}


if(mStr[i]=='B') {

i++;

int mv = mStr[i] - '0';

int cnt = C.wordloc;                                 //현재 word의 첫번째까지 글자 수


while(mv > 0) {

if(C.wordid == 1) {                              //범위 초과 시 미 이동

break;

}


mv--;

C.wordid--;

cnt += word.get(C.wordid).length();              //이동 총 글자수 합산

}


C.wordloc = 0;                                       //최종 word의 첫지점으로 위치 이동

C.loc -= cnt;                                        //cursor의 현재위치 update


while(word.get(C.wordid).charAt(C.wordloc) == '_') {  //첫지점이 "_"이면 아닌 지점까지 이동

C.loc++;

C.wordloc++;

}


continue;

}


if(mStr[i]=='D') {

i++;

int mv = mStr[i] - '0';


String tempfirst = word.get(C.wordid).substring(0,C.wordloc);  //현재 단어에서 지우는 지점 이전까지의 단어


if(mv > word.get(C.wordid).length()-C.wordloc) {               //지울 문자수가 현재 커서 위치에서 남은단어 수보다 큰 경우

mv -= word.get(C.wordid).length()-C.wordloc;

word.remove(C.wordid);

C.wordloc = 0;


if(C.wordid >= word.size()) {                              //지울 문자수가 남았지만 현재 단어가 마지막 단어인 경우

word.add(C.wordid,tempfirst);

C.wordid++;

continue;

}

}


while(mv > 0) {

if(C.wordid == word.size()) {                              //지우다가 끝까지 간 경우 

break;

}


if(mv > word.get(C.wordid).length()) {                     //지울 문자수가 단어수를 초과하면 단어 전체를 삭제

mv -= word.get(C.wordid).length();

word.remove(C.wordid);

}

else {

String templast = word.get(C.wordid).substring(C.wordloc+mv);  //지울 문자수가 단어수를 초과하지 않으면 지우고 남은 단어 저장

word.remove(C.wordid);


if(templast.length() == 0) {                                   //단어 마지막까지 지우면 다음단어를 붙여줄 대상으로 가져옴

templast = word.get(C.wordid);

word.remove(C.wordid);

C.wordloc = 0;

}


if(tempfirst.length() == 0 || (tempfirst.charAt(tempfirst.length()-1)!='_'&&templast.charAt(0)!='_')) {

word.add(C.wordid,tempfirst+templast);                     //위에서 앞쪽에 지우고 저장한 단어와 연결 가능하면 연결

C.wordloc = tempfirst.length();                            //앞단어 뒤쪽으로 커서 이동

}

else {

int chk = chkconnect(tempfirst);                           //단어 전체가 '_'면 1, 아니면 0


if(chk==1) {

templast = tempfirst + templast;                       //단어 전체가 '_'면 뒷단어에 붙이고 앞단어 길이만큼 wordloc을 뒤로 이동

C.wordloc += tempfirst.length();

tempfirst = "";

}


chk = chkconnect(templast);


if(chk==1) {                                               //단어 전체가 '_'이고 맨 마지막 위치가 아니면 뒷단어에 현재 단어를 붙임

if(C.wordid < word.size() - 1) {

templast = templast + word.get(C.wordid);

word.remove(C.wordid);

word.add(C.wordid,templast);

}

else {                                                 //단어 전체가 '_'이고 맨 마지막 위치면 앞단어에 붙임

templast = word.get(C.wordid-1) + templast;

C.wordid--;

C.wordloc = word.get(C.wordid).length() + C.wordloc;

word.remove(C.wordid);

word.add(C.wordid,templast);

}

}

else {

word.add(C.wordid,templast);                               //지운 후 단어 저장


if(tempfirst.length() > 0) {

word.add(C.wordid,tempfirst);                          //저장할 앞단어가 있으면 저장

}

}

}

mv = 0;

}

}


continue;

}


addword += mStr[i];

}


if(C.wordid == word.size()) {                                //cursor가 현재 끝 위치인 경우

if(addword.length() > 0) {

word.add(addword);

}

C.loc += addword.length();                               //단어 추가 후 다음 word 위치의 0번째로 cursor 위치 설정

C.wordid = word.size();

C.wordloc = 0;

}

else if(addword.length() > 0){                               //커서가 단어 중간인 경우

String currword = word.get(C.wordid);

String firstword = currword.substring(0,C.wordloc);

String lastword = currword.substring(C.wordloc);


word.remove(C.wordid);


C.loc += addword.length();



if(firstword.isEmpty() == false && (firstword.charAt(firstword.length()-1)=='_' || addword.charAt(0) == '_')) { //추가단어+앞단어 연결 불가 case 

word.add(C.wordid, firstword);                                            //앞단어 추가

C.wordid++;                                                               //커서를 추가 단어 뒤로 이동

C.wordloc = addword.length();

}

else {

C.wordloc += addword.length();                                            //커서를 현재 단어의 추가단어 뒤로 이동

addword = firstword+addword;                                              //앞단어와 합치기

}


if(addword.charAt(addword.length()-1)=='_' || lastword.charAt(0) == '_') {    //추가단어+뒷단어 연결 불가 case

word.add(C.wordid,addword);                                               //변경된 단어를 추가

C.wordid++;                                                               //커서를 다음단어 첫번째로 이동

C.wordloc = 0;

word.add(C.wordid,lastword);                                              //뒷단어 추가

}

else {

word.add(C.wordid,addword+lastword);                                      //현재 위치에 단어 합산하여 추가

}

}


if(nextword[0] >= 'A') {                         //2개 이상의 문자열 입력시 다음단어 추가를 위해 해당 함수 재귀 호출

putString(nextword);

}


char value;


if (C.wordid==word.size()) {                     //커서 위치가 마지막인 경우

value = '$';

}

else {

value = word.get(C.wordid).charAt(C.wordloc); //커서 현재위치 문자

}


return value;

}



public char getWord(int mX) {


if(mX > word.size()-1) {                          //범위 초과

return '$';

}


int i=0;

char value = word.get(mX).charAt(i);


while(value=='_') {                               //소문자 시작지점 찾기

i++;

value = word.get(mX).charAt(i);

}


return value;

}


public int chkconnect(String word) {

int value = 1;


for(int i=0;i<word.length();i++) {

if(word.charAt(i)!='_') {

value = 0;

break;

}

}


return value;

}

}
```
