# FFT Example

This repository serves as an example for [Yuyu378's FFTpack](https://github.com/Yuyu378/FFTpack). I have simplified the header and made some code modifications. You can extend this library to suit your specific application.

## Instructions
To get started, you can clone this repository and run the `main.c` file in your preferred IDE. If you are using VSCode as your IDE, the workspace folder (root) will generate a `tasks.json` file. In this file, you'll need to change "&{file}" to "${fileDirname}\\*.c" to ensure proper execution.

## Content
- Complex Fundamental Operations
- FFT (for any Length)
- Some DSP Operations

## Application

For fundamental FFT, it can only operate on lengths that are powers of 2. Yuyu378 has implemented a general version for FFT of any length, allowing you to use it for various DSP applications, such as convolution.
<br><br>

$$ x[n] * h[n] = \sum_{k=-\infty}^{\infty} x[k] \cdot h[n - k] $$

<br>

$$ \mathcal{F}\\{x * h\\} = \mathcal{F}\\{x\\} \cdot \mathcal{F}\\{h\\} $$

<br>
<hr>

<div align="left">
    <p><strong>Main Author (FFT)：</strong> Yuyu378</p>
    <p><strong>Edited by：</strong> D.S.</p>
</div>

<div align="right">
    <p><em>Last update date：2023 / 10 / 15</em></p>
</div>


