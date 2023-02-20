import sys
import os
import numpy as np
import scipy.stats as scistats


def linner_reg(x, y, n):
    x_mean = np.mean(x)
    y_mean = np.mean(y)
    beta1 = np.sum((x - x_mean) * (y - y_mean)) / np.sum((x - x_mean) ** 2)
    beta0 = y_mean - beta1 * x_mean
    
    y_estimate = beta1 * x + beta0
    residuals2 = (y - y_estimate) ** 2
    rss = np.sum(residuals2)
    rse2 = rss / (n - 2)
    tss = np.sum((y - y_mean) ** 2)
    
    r2 = (tss - rss) / tss
    se_beta1 = rse2 / np.sum((x - x_mean) ** 2) 
    se_beta0 = rse2 * (1 / n + (x_mean ** 2) / np.sum((x - x_mean) ** 2))
    
    t_beta1 = beta1 / np.sqrt(se_beta1)
    t_beta0 = beta0 / np.sqrt(se_beta0)
    
    p_beta1 = scistats.t.cdf(-t_beta1, n - 2) * 2
    p_beta0 = scistats.t.cdf(-t_beta0, n - 2) * 2

    f = (tss - rss) / (rss / (n - 2))
    p_f = 1 - scistats.f.cdf(f, 1 , n - 2)

    return beta0, beta1, rss, rse2, tss, r2, se_beta1, se_beta0, t_beta1, t_beta0, p_beta1, p_beta0




def main():
    x = np.array([1, 2, 3, 4, 5], dtype=np.double)
    y = np.array([1.9, 4.1, 6.1, 7.8, 10.1], dtype=np.double)
    beta0, beta1, rss, rse2, tss, r2, se_beta1, se_beta0, t_beta1, t_beta0, p_beta1, p_beta0 = linner_reg(x, y, len(x))
    print(beta0, beta1, rss, rse2, tss, r2, se_beta1, se_beta0, p_beta1)



if __name__ == "__main__":
    main()
