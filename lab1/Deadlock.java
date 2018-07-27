class A{
	synchronized void methodA(B b){
		b.last();
	}
	synchronized void last(){
		System.out.println("Inside A.last()");
	}	
}
class B{
	synchronized void methodB(A a){
		a.last();
	}
	synchronized void last(){
		System.out.println("Inside B.last()");
	}	
}
public class Deadlock implements Runnable{
	A a=new A();
	B b=new B();


	Deadlock(){
		Thread t = new Thread(this);
		int count = 1500;

		t.start();
		while(count-->0)；
		a.methodA(b);
	}

	public void run(){
		b.methodB(a);
	}
	public static void main(String args[]){
		new Deadlock();
	}

}
