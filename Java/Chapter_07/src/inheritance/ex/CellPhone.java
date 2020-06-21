package inheritance.ex;

// 상속
// 부모 클래스
public class CellPhone {

	// 필드
	String model; 
	String color;
	
	// 생성자
	
	// 메서드
	void powerOn() {
		System.out.println("전원을 켭니다.");
	}
	
	void powerOff() {
		System.out.println("전원을 끕니다.");
	}
	
	void bell() {
		System.out.println("벨이 울립니다.");
	}
	
	void sendVoice(String message) {
		System.out.println("자기: "+message);
	}
	
	void receiveVoice(String message) {
		System.out.println("상대방: "+message);
	}
	
	void hangUp() {
		System.out.println("전화를 끊습니다.");
	}
}
