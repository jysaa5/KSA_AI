package inheritance.ex;

// ���
// �ڽ� Ŭ����
public class DmbCellPhone extends CellPhone {
	
	// �ʵ�
	int channel;
	
	// ������
	DmbCellPhone(String model, String color, int channel){
		// CellPhone Ŭ�����κ��� ��ӹ��� �ʵ�
		this.model = model;
		this.color = color;
		this.channel = channel;
	}
	
	
	// �޼���
	void turnOnDmb() {
		System.out.println("ä�� "+channel + " �� DMB ��� ������ �����մϴ�.");
	}

	
	void changeChannelDmb(int channel) {
		this.channel = channel;
		System.out.println("ä�� "+ channel + "������ �ٲߴϴ�.");
	}
	
	void turnOffDmb() {
		System.out.println("DMB ��� ������ ����ϴ�.");
	}
	
}
