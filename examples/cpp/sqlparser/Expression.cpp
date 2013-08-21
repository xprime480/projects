  class True : public Expression
  {
  public:
    virtual ExpressionValue value() 
    { 
      ExpressionValue ev; 
      ev.tag = ExpressionValue::EV_BOOL;
      ev.value.b = true;
      return ev;
    }
  };

  class False : public Expression
  {
  public:
    virtual ExpressionValue value()
    { 
      ExpressionValue ev; 
      ev.tag = ExpressionValue::EV_BOOL;
      ev.value.b = false;
      return ev;
    }
  };
