numpp
========

| **Build** | **Docker image** | **Style** |
|--------------------|----------------------------|------------------|
| ![Build Status](https://travis-ci.org/vyzyv/numpp.svg?branch=master) | [![Docker Status](https://img.shields.io/badge/docker-passing-blue.svg)](https://hub.docker.com/r/vyzyv/numpp/) | [![Codacy Badge](https://api.codacy.com/project/badge/Grade/4708552f40f3405cb80ed14a455d15f4)](https://www.codacy.com/app/vyz/numpp?utm_source=github.com&utm_medium=referral&utm_content=vyzyv/numpp&utm_campaign=badger) | 

**numpp** is an open source numerical library aimed at maximizing runtime efficiency 
by performing every calculation during the compilation step.

  Currently it consists of **3 differentiation ways**, **linear algebra structures**, **root finding methods**.

  It trims the runtime by using cutting edge **C++17** features, **template metaprogramming**,
  numerical ideas seen in **recent numerical research papers** and many others.

  Furthermore, it is template only, hence easy to install (via repo cloning and copying 
  or using the image provided in the banner docker image).

How does it compare?
====================

## 1. Most promising module

  Best looking part is, without a doubt, **symbolic differentiation**.

    Thanks to researchers from this paper: **https://arxiv.org/abs/1705.01729** and some improvements of mine,
  it seems, that it can achieve around **10x speedup or more** in derivative evaluations against **SymPy**
  which approaches **efficiency of hand-coded derivatives**.
  When it comes to memory it should use 0b as it's only type based.

  For thorough compilation times comparison, I urge you to check their scientific paper!
     **Credits for the squeezer idea and being first to publish it go to academics mentioned above.**

## 2. Overall Runtime speedup

  **30 x** speedups in matrix multiplication is not uncommon (compared to **Eigen**), 
  and binaries created are shorter by about the same amount. 
  In other areas, for example numerical differentiation, speed up over **GSL** can exceed **50x**.

## 3. Compilation times

  I'm not going to lie, this is the place, where some modules lose a lot in favor of competition. 
  In the case of matrix multiplication, memory bandwith and **lack of parallelism during compilation**
  slows the matrix operations by a few seconds even. When comparing to GSL such drop hasn't beend noticed.

Installation:
=============

**1. Normal installation**
  Just clone this repository into your /usr/include/ path or other performing the same functionality. 
  It needs GCC7.0 or more for it to work. It should work for Clang as well, but it wasn't thoroughly tests
 
**2. Dockerized installation**
  If your distro doesn't have GCC7.0 just run the image provided in the banner at the top via command:
  **docker run -i -t vyzyv/numpp:latest /bin/bash** to enter the container, which has everything you need to
  run your applications based on **numpp**.

Documentation:
==============

For more specific informations about what the library has to offer check below:
<link to gh-pages>

For in-depth dissertation of provided functionality check the paper below and others linked inside:
<link to dissertation>

Contributions:
==============

Currently looking for **contributors with interesting numerical ideas** and all those 
willing to perform additional testing, expand documentation or **implement their/someones (with permission and credits)**
