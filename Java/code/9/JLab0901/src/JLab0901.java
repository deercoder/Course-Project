import java.applet.Applet;
import java.awt.*;

public class JLab0901 extends Applet{
	private int initCnt;
	private int startCnt;
	private int stopCnt;
	private int destroyCnt;
	private int paintCnt;
	public void LifeCycle(){
		initCnt = 0;
		startCnt = 0;
		stopCnt = 0;
		destroyCnt = 0;
		paintCnt = 0;
	}
	public void init(){
		initCnt++;
		System.out.println("init() invoked "+initCnt+" time(s)");
	}
	public void destroy(){
		destroyCnt++;
		System.out.println("destroy() invoked "+destroyCnt+" time(s)");
	}
	public void start(){
		stopCnt++;
		System.out.println("stop() invoked "+stopCnt+" time(s)");
	}
	public void paint(Graphics g){
		paintCnt++;
		System.out.println("paint() invoked "+paintCnt+" time(s)");
		g.drawLine(20, 200, 300, 200);
		g.drawLine(20, 200, 20, 200);
		g.drawLine(20, 170, 15, 170);
		g.drawLine(20, 140, 15, 140);
		g.drawLine(20, 110, 15, 110);
		g.drawLine(20, 80, 15, 80);
		g.drawLine(20, 50, 15, 50);
		g.drawString("init()",25, 213);
		g.drawString("start()",75, 213);
		g.drawString("stop",125, 213);
		g.drawString("destroy()",175, 213);
		g.drawString("paint()",235, 213);
		g.fillRect(25,200-initCnt*30,40,initCnt*30);
		g.fillRect(75,200-startCnt*30,40,startCnt*30);
		g.fillRect(175,200-destroyCnt*30,40,destroyCnt*30);
		g.fillRect(235,200-paintCnt*30,40,paintCnt*30);
	}
}
