
import Gorf;

class Yuch {
    //
    public native int quizling();
    
    public native void nobble( int x );

    public int krab( double a, double b ) {
        if ( a > b ) {
            return -1;
        }
        if ( b > a ) {
            return 1;
        }
        return 0;
    }

    public static void main( String[] args ) {
        int  l = args.length;
        Yuch y = new Yuch();
        int  q = y.quizling();
        System.out.println( "Yuch " + q );
        y.nobble( l );
        Gorf g = new Gorf( q );
        System.out.println( "Gorf " + g.kazz( l ) );
    }

    static {
        System.loadLibrary( "Yuch" );
    }
}
