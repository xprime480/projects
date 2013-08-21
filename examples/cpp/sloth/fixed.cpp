{
  if ( values.empty() ) {
    return makeNil();
  }

  vector<int>::const_iterator iter;
  iter = values.begin();
  Form h = makeInt(*iter);

  Form t;
  ++iter;
  if ( iter = values.end() ) {
    t = makeNil();
  }
  else {
    t = makeDelayed(vector<int>(iter, values.end()));
  }
  
  return makeSequence(h, t);
}
