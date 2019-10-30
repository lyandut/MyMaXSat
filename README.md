# MyMaXSat

The C++ implementation of the four approximation algorithms for  **Maximum Satisfiability  Problem**.

| Symbol                      | Definition                | Description                                                  | Type     |
| --------------------------- | ------------------------- | ------------------------------------------------------------ | -------- |
| $x_{i}$                     | *Variable*                | 变元，$x_{i}+\bar x_{i}=1$                                   | bool     |
| $C_{i}$                     | *Clause*                  | 子句，$C_{i}=\left(\bigvee_{i \in S_{i}^{+}} x_{i}\right) \vee\left(\bigvee_{i \in S_{i}^{-}} \bar{x}_{i}\right), i=1,2,...,m$ | bool     |
| $W_{i}$                     | *Weight*                  | 权重，对应子句 $C_{i}$ 的权重                                | integer  |
| $CNF / WCNF$                | *Formula*                 | (带权)合取范式，$CNF=\bigwedge_{i \in S} C_{i}$， $WCNF=\bigwedge_{i \in S} C_{i} \left\{ W_{i} \right\}$ | /        |
| $E\left[ Z_{i} \right]$     | *Expectation*             | 期望，对应字句 $C_{i}$ 被满足的期望                          | floating |
| $E\left[ Z | x_{i} \right]$ | *Conditional Expectation* | 条件期望，在 $x_{i}$ 确定取值前提下，$CNF$ 被满足的期望      | floating |
| $E\left[ Z \right]$         | *Total Expectation*       | 总期望，$CNF$ 被满足的期望                                   | floating |

- **Maximum Satisfiability**：找到一组 $x_{i}$ 的取值，使满足的子句数目 $\left| C_{i} \right|$ 最大。 
- **Maximum Weight Satisfiability**：找到一组 $x_{i}$ 的取值，使满足的子句权重之和 $\sum_{i \in S} \left| C_{i} \times W_{i} \right|$ 最大。
- **Hard Clause & Soft Clause**：在 *Maximum Weight Satisfiability* 中，必须满足的子句称为硬子句，允许部分满足的子句称为软子句；但求解器一般不会判断子句类型（增加无意义的时空开销），而是通过**赋予硬子句一个大于所有软子句权重之和的权重**（即使满足所有软子句都不如满足一个硬子句获取的权重收益大），使求解器能自适应满足软硬子句约束。



# Algorithms

##  Randomized Algorithm

- 算法描述：将 $x_{i}$ 分别以 $1/2$ 的概率设置为 0 或 1，则 $C_{i}$ 被满足的期望为 $E\left[ Z_{i} \right] = 1-2^{\left| C_{i} \right|}$，$CNF$ 被满足的期望为 $E\left[ Z \right] = \sum_{i=1}^{m} E\left[ Z_{i} \right] = \sum_{i=1}^{m} \big( 1-2^{\left| C_{i} \right|} \big)$。
- 算法流程：
- 近似比：



##  Derandomized Algorithm

- 算法描述：在算法①的基础上，每个变元 $x_{i}$ 都有 $1/2$ 的概率取 0 或 1，即$E\left[ Z \right] = \frac{1}{2} E\left[ Z | x_{i}=1 \right] + \frac{1}{2} E\left[ Z | x_{i}=0 \right]$。对于每个变元 $x_{i}$，比较 $\frac{1}{2} E\left[ Z | x_{i} = 1 \right]$ 和 $\frac{1}{2} E\left[ Z | x_{i} = 0 \right]$ 的大小，取其中较大的期望值
- 算法流程：
- 近似比：



##  LP Rounding Algorithm 

$$
\begin{array}{ll}{\text { maximize: }} & {\sum_{i=1}^{m} q_{i}} \\ {\text { s.t. }} & {q_{i} \leq \sum_{j \in S_{i}^{+}} y_{j}+\sum_{j \in S_{i}^{-}}\left(1-y_{j}\right) \quad \forall i} \\ {} & {q_{i}, y_{j} \in\{0,1\}}\end{array}
$$







## LP Derandomized Algorithm







