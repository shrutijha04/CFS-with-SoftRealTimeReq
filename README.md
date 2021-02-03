# CFS-with-SoftRealTimeReq

Course Project for Operating Systems (CSE231)

Modifying CFS Scheduler via system call in linux kernel


## Details:

* The problem statement is to add a system call in Linux to allow adding a **Soft Realtime Requirement** to each process- where the requirement is say x for a process with pid PID.

* Now we need to modify the CFS scheduler so that every time the scheduler is called, you need to check if the real-time guarantees of process with soft-realtime requirements are being met or not. You would give higher priority to a processes soft-realtime requirement compared to the vruntime that is normally
considered.

* You would thus need to modify the scheduler in such a way that when everytime a process is selected through the RB-tree, you you need to compare to all other process with soft-realtime requirements and see which one of those require the CPU more urgently than the one selected through the regular RB- tree. The one that urgently requires CPU time need to be scheduled before the one selected through CFS.

## Implementation

Refer to documentation pdf for explanation of how this was implemented.
