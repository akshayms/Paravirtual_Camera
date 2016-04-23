# Paravirtual Camera

## Introduction
Currently, the only way for the camera hardware to be associated with a virtual machine is through the PCI pass-through mechanism. But PCI pass-through removes the camera hardware from the host machine and attaches it to the VM, thereby preventing the true nature of shareable hardware. In this project, we have tried to overcome this problem by using mechanisms provided by the Virtio library.

## Technical details
Virtio provides channels between the host machine and the VM through ring buffers. In our implementation, we created a socket file through Virtio which appears as a character device in the VM and passed images through the socket. When the camera is launched in the VM, the V4L2 driver will try to read the image from the character device exposed rather from underlying vendor specific camera drivers.

## Scope for Improvement
In the current implementation, we have developed more of a push mechanism wherein the content is pushed to the VM. In an ideal situation, the camera application in the VM should read content from the character device when required.
