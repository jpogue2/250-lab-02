# Lab 2
[Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repo and clone it to your machine to get started!

## Team Members
- team member 1: Jeremy Pogue
- team member 2: Kaelyn Cho
- Note: We worked independently, but helped each other when stuck.

## Lab Question Answers

Answer for Question 1: 

When 50% loss was added to the local environment for UDP, the reliability was halved (about 50% of messages were successfully passed from one terminal to the other). This occurred because, when UDP fails to send something, it doesn't retry to send it. Therefore, whenever the server was busy and unable to send a message, the input would simply be lost. 

Answer for Question 2:

When 50% loss was added to the local environment for TCP, the reliability was unchanged. This occurred because, whenever the TCP was unable to send something, it would continue trying to send it until success. Therefore, all user input was sent eventually. However, there was latency in the responses as a result.

Answer for Question 3:

The speed of the TCP response was significantly slower. This is because, every time a message was lost, TCP would retry sending the message until it succeeded. Obviously, this process takes time, which resulted in high latency. 
