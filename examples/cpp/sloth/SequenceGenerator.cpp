
#include "Form.h"
#include "FormFactory.h"

#include "SequenceGenerator.h"

using namespace Sloth;

Form SequenceGenerator::headFromNil() const
{
  return FormFactory::makeMessage("head of an empty sequence not defined");
}
