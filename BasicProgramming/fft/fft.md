# 快速傅里叶变换：大数乘法和除法

众所周知，我们可以把一个 $n$ 位的 $p$ 进制数写成：
$$
a = \sum_{i=0}^{n-1} a_ip^i.
$$

那么借助函数思维，本质上，我们是在考虑如下的多项式函数之间的运算：

$$
a(x) = \sum_{i=0}^{n-1} a_ix^i.
$$

进而，考虑两个大数 $a$ 和 $b$ 的乘法，我们只需要计算 $a(x)$ 和 $b(x)$ 的乘法就可以了，然后我们代入 $x=p$，就可以得到我们想要的答案。

刚好，我们的$n$次单位根同学 $\zeta_n^k=\mathrm{e}^{2\pi\mathrm{j}k}$ 有着非常好的性质，这就是所谓 $Gauss$ 和：
$$
\frac{1}{n}\sum_{i=0}^{n-1} \zeta_n^{ki}=
\frac{1}{n}\sum_{i=0}^{n-1} \mathrm{e}^{2\pi\mathrm{j}ki}=\begin{cases}1,k\equiv 0\bmod p,\\0, k\not\equiv 0\bmod p.\end{cases}
$$

这会让我们在计算多项式乘法的时候展现出魔法，因为我们发现：
$$
\frac{1}{n}\sum_{k=0}^{n-1}a(\zeta_n^k)\zeta_n^{-km} = \sum_{k=0}^{n-1}\sum_{j=0}^{n-1} a_j\zeta^{(j-m)k}_n = a_m.
$$
这意味着我们可以通过计算多项式在若干点上的值的加权和来得到多项式的系数，进一步我们发现：
$$
\begin{split}
ab(\zeta_n^k)&=a(\zeta_n^k)b(\zeta_n^k)\\
&=(\sum_{i=0}^{n-1} a_i\zeta^{ik}_n)(\sum_{j=0}^{n-1} b_j\zeta^{jk}_n).
\end{split}
$$

而
$$
(ab)_m=\frac{1}{n}\sum_{k=1}^{n-1}(ab)(\zeta_n^k)\zeta_n^{-km}.
$$

你没发现这些东西长得贼像吗？不妨设：
$$
\mathcal{F}\{a\}(k)=a(\zeta_n^k)=\sum_{i=0}^{n-1} a_i\zeta^{ik}_n.
$$

那么上面这些式子就可以写成：
$$
\mathcal{F}\{ab\} (k)= ab(\zeta_n^k)=\mathcal{F}\{a\} (k)\mathcal{F}\{b\} (k)
$$
$$
(ab)_m = \frac{1}{n}\sum_{k=1}^{n-1}\mathcal{F}\{ab\} (k)\zeta_n^{-km}=\frac{1}{n}\overline{\mathcal{F}\left\lbrace\overline{\mathcal{F}\{ab\}(k)}\right\rbrace(n)}.
$$

恭喜，你发现的这个$\mathcal{F}\{a\}$就叫作离散傅里叶变换。

