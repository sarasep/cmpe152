/**
 * <h1>IfExecutor</h1>
 *
 * <p>Execute an IF statement.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <vector>
#include "WhenExecutor.h"
#include "StatementExecutor.h"
#include "ExpressionExecutor.h"
#include "../../../DataValue.h"
#include "../../../intermediate/ICodeNode.h"
#include "../../../intermediate/icodeimpl/ICodeNodeImpl.h"

namespace wci { namespace backend { namespace interpreter { namespace executors {

using namespace std;
using namespace wci;
using namespace wci::backend::interpreter;
using namespace wci::intermediate;
using namespace wci::intermediate::icodeimpl;


//Git push

WhenExecutor::WhenExecutor(Executor *parent)
    : StatementExecutor(parent)
{
}

DataValue *WhenExecutor::execute(ICodeNode *node)
{

    vector<ICodeNode *> children = node->get_children();

    ExpressionExecutor expression_executor(this);
    StatementExecutor statement_executor(this);
    bool flag  = true;

    for(int i = 0 ; i < (children.size() - 1 ); i++)
    {
        if(i%2 == 0)
        {
            ICodeNode *else_s= children[i];
            DataValue *data_value = expression_executor.execute(else_s);
            if (data_value->b)
            {
                flag = false;
                break;
            }

        }
        else{
            ICodeNode *statement= children[i];

            statement_executor.execute(statement);
        }
    }

    if(flag){

        ICodeNode *new_i = children[(children.size() - 1)];
        statement_executor.execute(new_i);

    }

    ++execution_count;  // count the IF statement itself
    return nullptr;
}

}}}}  // namespace wci::backend::interpreter::executors
