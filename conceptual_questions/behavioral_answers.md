# Behavioral Questions

### What do you know about the company and what we do?
Research company before hand. Try to understand their values, products, market, etc..

### Why do you want to join the company?
Express interest in the projects and technology they use. Could also mention the company values and how they align with yours.

### What is your biggest strength?
Typical answers include problem solving. Mention something unique/thoughtful and give an example.

### What is your biggest weakness?
Answer should include how you're working to improve your weaknesses.

### Tell me about a time when you had to unblock yourself. 
Talk about the blocker, what you did to fix it, and the outcome. Blocker can be technical (lack of expertise), schedule based, or resource based. Answer should demonstrate that you show initiative, resourcefulness, independence, and are willing to learn.

Example:
A coworker was out on a long vacation and was tasked with bringing up a board that I needed to interact with. My code would communicate with my code over UART and had to be completed very soon to stay on schedule. Instead of working on the official board that I had no expertise in, I developed an emulator on an raspberry pi. The emulator received and responded to UART message the way it would on the official board and included an interface for simulating new data updates.

### Tell me about a time when a feature could not be completed in the required time. What compromises did you have to make? How did you resolve the issue?


### Tell me about a time when you had to handle a disagreement or conflict with a colleague on a technical project. How did you approach it, and what was the outcome?

### Tell me about a time you had to debug a difficult hardware–software integration problem.

### How do you approach reviewing embedded code written by another engineer?
Mention:
1. Correctness - Does the code function like its supposed to
2. Bugs/Mistakes - Correct any mistakes
3. Guidelines - Does it conform with our coding guidelines. I.e. it should use dynamic memory, uninitialized vars, etc.. Style guidelines might be included, but that can be checked with a linter
4. Suggestions - Suggest improvements to make code more robust or scalable.
5. Nit picks - Least important, but maybe include your nits like spelling/grammar mistakes in comments, etc.

Do not be critical when review. Try to phrase your comments politely.

### There is a rare crash that occurs once every few days. How would you debug it? What are common causes of long-interval crashes?

Collect as much data as possible and try to determine the overall state of the system at the time of the crash. Is the system idle? Or is there some event/process occurring before the crash. Check for error and warnings messages. Look at data related to common problems including:
1. Memory usage/leaks/fragmentation
2. Networking errors like corrupt packets. Packet corruption is rare but could occur over long periods of time.
3. Integer overflows related to timing or accumulation of data/events.

### Talk about some of the projects you worked on. What were some challenges and how did you overcome them?

### Say you have a spacecraft that reads from multiple sensors for a critical mission and you know one of the sensors is faulty. How would you deal with it?

### Tell me about a time when you had to mentor or train a junior engineer or teammate. How did you help them grow, and what was the result?
Mention:
- Building rapport
- Understanding their level of knowledge of the system and general expertise
- Assign tasks with increasing difficulty/complexity. Should assign tasks that are simple at first so they get a feel for the system. Then assign more difficult tasks or tasks different areas.
- Provide advice and help when requested, but don't hold their hand
- Do routine check-ins/one-on-ones. 

### Tell me about a time when you had to solve a difficult engineering challenge.
