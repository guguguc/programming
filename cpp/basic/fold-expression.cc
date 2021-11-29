#include <iostream>


/* C++17
 * E: 包含未扩展参数pack的表达式
 * I: 不包含未扩展参数pack的表达式
 * 1. 一元右折叠 ( E op ...)
 *    ( (E1 op (... op (E_{n-1} op E_n)) )
 * 2. 一元左折叠 ( ... op E_n )
 *    ( ((E_1 op E_2) op ...) op E_n)
 * 3. 二元右折叠 (E op ... op I)
 *    ( E_1 op (... op E_{n-1})) op (E_n op I))
 * 4. 二元左折叠 (I op ... op E)
 *    ( (((I op E_1) op E2) op ...) op E_n)
 */
template<typename ...Args>
void display(Args&&... args)
{
    (std::cout << ... << args) << "\n";
}

int main()
{
    display("sad", "asdljad", "jasdlad", 1, 2);
}
