
import java.lang.Math;

public class Gorf {
    public Gorf( int v ) {
	this.val = v;
	this.ddd = Math.random();
    }

    public native int kazz( int x );

    public static void main( String[] args ) {
	Gorf g = new Gorf( 6 );
	g.ddd = 4.02341;
	g.kazz( 7 );
    }

    private int val;
    private double ddd;

    static {
	System.loadLibrary( "Gorf" );
    }
}
