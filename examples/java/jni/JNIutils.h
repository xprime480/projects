
#include <jni.h>

namespace utils
{
  namespace jni
  {
    /*!
      \brief implement most of the JNI operation to get a field

      Template parameter T specifies the JNI type of the target field
    */
    template < typename T >
    class JniFieldGetterBase
    {
    public:
      /*!
	\brief constructor
    
	\param e the JNI environment
	\param o a Java object
      */
      JniFieldGetterBase( JNIEnv *e, jobject o )
	: env( e )
	, obj( o )
      {
	cls = env->GetObjectClass( obj );
      }

      /*!
	\brief get the value
    
	\param fld field name
	\param val placeholder for the value

	\return true iff the value was successfully retrieved.
      */
      bool getValue( char const * fld, T & val )
      {
	fid = getField( fld );
	if ( fid == NULL ) {
	  return false;
	}

	// get the value

	getValue( val );

	return true;
      }

    protected:
      /*!
	\brief save the environment
      */
      JNIEnv *env;

      /*!
	\brief save the object
      */ 
      jobject obj;

      /*!
	\brief the class of \a obj
      */
      jclass cls;

      /*!
	\brief the field identifier
      */
      jfieldID fid;

      /*!
	\brief get the field identifier
	
	\param fld the field name
	
	\return the field ID, or NULL on failure
      */
      virtual jfieldID getField( char const * fld ) = 0;

    private:
      void getValue( jint & val )
      {
	val = env->GetIntField( obj, fid );
      }
      void getValue( jdouble & val )
      {
	val = env->GetDoubleField( obj, fid );
      }
    };

    template< typename T >
    class JniFieldGetter : public JniFieldGetterBase< T >
    {
    public:
      JniFieldGetter( JNIEnv *e, jobject o )
	: JniFieldGetterBase< T >( e, o )
      {
      }

      virtual jfieldID getField( char const * )
      {
	return NULL;
      }
    };

    template<>
    class JniFieldGetter< jint > : public  JniFieldGetterBase< jint >
    {
    public:
      JniFieldGetter( JNIEnv *e, jobject o )
	: JniFieldGetterBase< jint >( e, o )
      {
      }

      virtual jfieldID getField( char const * fld )
      {
	return env->GetFieldID( cls, fld, "I" );
      }
    };
      
    template<>
    class JniFieldGetter< jdouble > : public  JniFieldGetterBase< jdouble >
    {
    public:
      JniFieldGetter( JNIEnv *e, jobject o )
	: JniFieldGetterBase< jdouble >( e, o )
      {
      }

      virtual jfieldID getField( char const * fld )
      {
	return env->GetFieldID( cls, fld, "D" );
      }
    };
      
    template < typename T >
    bool getJniFieldValue( JNIEnv *env, jobject obj, char const * fld, T & val)
    {
      // get a reference to the field

      JniFieldGetter< T > getter( env, obj );
      return getter.getValue( fld, val );
    }
  }
}
