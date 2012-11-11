import java.applet.Applet;
import java.awt.Graphics;
public class JLab0902 extends Applet{
	private  String s="";
	private int x;
	private int y;
	private int x2;
	private int y2;
	public void init(){
		s = getParameter("vstring");
		x = Integer.parseInt(getParameter("x"));
		y = Integer.parseInt(getParameter("y"));
		x2 = Integer.parseInt(getParameter("x2"));
		y2 = Integer.parseInt(getParameter("y2"));
	}
	public void paint(Graphics g){
		if(s != null){
			g.drawString(s, x, y);
			g.drawLine(x,y,x2,y2);
		}
	}
}
