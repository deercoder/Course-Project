import java.util.Calendar;
public class JLab0604 {
	public static void main(String[] args) {
		final String dayNames[] = { "星期日", "星期一", "星期二", "星期三", "星期四", "星期五","星期六" };
		Calendar   calendar   =   Calendar.getInstance();   
		int   month   =   calendar.get(Calendar.MONTH)+1;
		int   year    =   calendar.get(Calendar.YEAR);
		int   date 	  =   calendar.get(Calendar.DATE);
		int   dayOfWeek  = calendar.get(Calendar.DAY_OF_WEEK);
		System.out.print("今天是 ");
		System.out.print(year+" 年  ");
		System.out.print(month+" 月  ");
		System.out.print(date+" 日  ");
		System.out.print(dayNames[dayOfWeek-1]);
	}
}
