# 数値解析04

#### 34番 藤澤直樹

## オイラー法について答えなさい

### 適当な常微分方程式を一つ取り上げ、刻み幅(分割数)と真値との差(誤差)を検討しなさい。

常微分方程式として
$$
\begin{eqnarray}
\frac{dy}{dx} = xy
\end{eqnarray}
$$
について考える


|分割数|結果|誤差|
|:---|:---|:---|
|1|1|0.64872|
|2|1.25|0.39871|
|4|1.41943|0.22928|
|8|1.52400|0.12471|
|16|1.58338|0.06533|
|32|1.61523|0.03348|
|64|1.63176|0.01695|
|128|1.64018|0.00853|
|256|1.64444|0.00427|
|512|1.64657|0.00214|
|1024|1.64764|0.00107|

分割数が増えるごとに，正確な値に近づいていくことがわかる．

### オイラー法による解法から考えて誤差の出る理由を説明しなさい。

オイラー法は、短い直線を連続的につなげて疑似的な曲線を作ることで元の関数に似せるという方法である。分割数を無限にすることで完全に関数を再現することができるが、有限数である限り連続ではない場所ができてしまい、そこから誤差が出てしまうと考えられる。

### どのような微分方程式であればオイラー法でも誤差が出ないことになるか。また、プログラムを実行し試してみなさい(刻み幅によらず誤差が出ない)。

関数が直線であれば刻み幅によって差が出ないとできるため微分値が定数な関数は誤差が出ない.
例えば以下のようなものである.

$$
\begin{eqnarray}
\frac{dy}{dx} = 1
\end{eqnarray}
$$
<div style="page-break-before:always"></div>
## ルンゲ・クッタ法で解きなさい．

### 次の微分方程式を解きなさい.初期値(x=1, y=1)とし，xが2のときyの値を誤差0.1%未満で求める.このときの刻み幅を検討しなさい.

$$
\begin{eqnarray}
\frac{dy}{dx} = \frac{3y}{1+x}
\end{eqnarray}
$$

|分割数|結果|誤差|誤差率(%)|
|:---|:---|:---|:---|
|1|3.3466666666666667|0.02833333333333332|0.8466135458167326|
|2|3.3719181716151407|0.0030818283848592642|0.09139689126510077|
|4|3.3747463393212493|0.0002536606787506557|0.007516436888755127|
|8|3.3749818678488928|0.000018132151107241867|0.000537251808075601|

よって分割数2以上で誤差率0.1%未満となる.

<div style="page-break-before:always"></div>
以下 プログラムリスト

```javascript
// 解答を出力するブロックを取得
var ansForm = document.getElementById('ans-field');

/**
 * euler's Method
 * @param  {fx/dx} func
 * @param  {document} form
 */
function euler (func, form) {
  const a = 0, b = 1, eta = 1;
  let ans = document.createElement('table');

  for (let i = 0; i < 11; i++) {
    const N = Math.pow(2, i);

    const h = (b - a) / N;

    let x = a;
    let y = eta;

    while (x < b) {
      y = y + h * func(x, y);
      x += h;
    }

    const row = ans.insertRow();
    const cel1 = row.insertCell();
    cel1.innerText = "N=" + N + "  ";
    const cel2 = row.insertCell();
    cel2.innerText = "y=" + y + "  ";
    const cel3 = row.insertCell();
    cel3.innerText = ""+ Math.abs(1.64872 - y);
  }
  ansForm.appendChild(ans);
}

function main () {
  const func = function (x, y) {
    return eval(document.getElementById('fx').value);
  }
  ansForm.innerHTML = "";
  euler (func, ansForm);
}
```
<div style="page-break-before:always"></div>
```javascript
// 解答を出力するブロックを取得
var ansForm = document.getElementById('ans-field');

/**
 * Runge-Kutta's Method
 * @param  {fx/dx} func
 * @param  {document} form
 */
function rungeKutta (func, form) {
  const a = 1, b = 2, y0 = 1;
  let ans = document.createElement('table');

  for (let i = 0; i < 11; i++) {
    const N = Math.pow(2, i);

    const h = (b - a) / N;

    let x = a;
    let y = y0;

    while (x < b) {
      const k1 = func(x, y);
      const k2 = func(x + h / 2, y + k1 * h / 2);
      const k3 = func(x + h / 2, y + k2 * h / 2);
      const k4 = func(x + h, y + k3 * h);

      y = y + h * (k1 + 2 * k2 + 2 * k3 + k4) /6;
      x += h;
    }

    const row = ans.insertRow();
    const cel1 = row.insertCell();
    cel1.innerText = N;
    const cel2 = row.insertCell();
    cel2.innerText = y;
    const cel3 = row.insertCell();
    cel3.innerText = 3.375 - y;
    const cel4 = row.insertCell();
    cel4.innerText = (3.375 - y) / y * 100;
  }
  ansForm.appendChild(ans);
}

function main () {
  const func = function (x, y) {
    return eval(document.getElementById('fx').value);
  }
  ansForm.innerHTML = "";
  rungeKutta (func, ansForm);
}
```
