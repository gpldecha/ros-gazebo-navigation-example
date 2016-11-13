#include "online_search/online_search.h"
#include <assert.h>
#include <limits>

namespace search{

Online_search::Online_search(const arma::Mat<int> &Adj,const objective_func& obj_func)
    :Adj(Adj),obj_func(obj_func)
{
    s_c = 0;
    s_l = 0;
    value = 0;
    optimal_action = action::four;
}

void Online_search::update_state(const arma::rowvec2& agent_pos,const arma::mat& grid){
    s_c  = 0;
    dist = arma::norm(agent_pos - grid.row(0));
    for(std::size_t j = 1; j < grid.n_rows;j++){
        tmp = arma::norm(agent_pos - grid.row(j));
        if(tmp < dist)
        {
            dist = tmp;
            s_c  = j;
        }
    }
}

action Online_search::get_action(std::size_t max_depth){

    s_l     = s_c;
    value   = 0;
    depth_first_search(s_l,s_c,value,optimal_action,0,max_depth);
    return optimal_action;
}

void Online_search::depth_first_search(state s_l,state s_c,double& value,action& optimal_action,std::size_t depth, std::size_t max_depth)
{

    if(depth > max_depth)
        return;

    state s_n;
    action a;
    for(std::size_t i = 0; i < actions.size();i++)
    {
        a                   = actions[i];
        s_n                 = forward_dynamics(s_c,a,Adj);
        std::cout<< "   f(" << s_c << "," << action2int(a) << ") = " << s_n << std::endl;
        Q[action2int(a)]    = obj_func(s_l,s_c,s_n);

        if(s_n != -1 && depth+1<max_depth)
        {
            depth_first_search(s_c,s_n,value,optimal_action,depth+1,max_depth);
        }

    }
    // arg max Q(s,a)
    get_max(value,optimal_action,Q);
}

void Online_search::get_max(double& value, action &a, const std::array<double,4>& Q){

    a       = actions[0];
    value   = Q[action2int(a)];

    for(std::size_t i = 1; i < actions.size(); i++)
    {
        if(Q[action2int(actions[i])] > value)
        {
            a       = actions[i];
            value   = Q[action2int(a)];
        }
    }

}

void Online_search::print() const{
    std::cout<< "(Online_search)" << std::endl;
    std::cout<< "   s_l: "        << s_l << std::endl;
    std::cout<< "   s_c: "        << s_c << std::endl;
    std::cout<< "   Q:   ";
    for(std::size_t i = 0; i < Q.size();i++)
    {
        std::cout<< Q[i] << " ";
    }
    std::cout<< std::endl;
    std::cout<< "  op a: " << action2int(optimal_action) << std::endl;

}






}
