package constructor.ex;

public class Car {
	
	String company = "�����ڵ���";
	String model;
	String color;
	int maxSpeed;
	
	
	//������
	Car() {}
	
	
	//Car(String model){
	//	this.model = model;
	//}
	
	Car(String model){
		this(model, "����", 250);
	}
	
	
	//Car(String model, String color){
	//	this.model = model;
	//	this.color = color;
		
	//}
	
	
	Car(String model, String color){
		this(model, color, 250);
	}
	
	
	Car(String model, String color, int maxSpeed){
		this.model = model;
		this.color = color;
		this.maxSpeed = maxSpeed;
	}

	
	
}
