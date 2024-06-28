<h1> Design Doc </h1>

<h3> Idea: </h3>
<ul>
    <li>Name: BuissAI</li>
    <li>Goal: A customizeable AI for business to customize for their item needs</li>
    <li>
        Detail: Users will provide a file which maps prices, names and counts of items <br>
        and the AI must read these values and answer questions about the quantity and price of items.
    </li>
</ul>

<h3> Tools: </h3>
<ul>
    <li>Language: C</li>
    <li>Reason: Although tools such as <i>Tenserflow</i> and <i>PyTorch</i> exist, they limit the learning process <br>
            and true understanding of machine learning which I am seeking.
    </li>
</ul>

<h3> Process: </h3>
<ol>
    <li> Use numbers to get a basic understanding of how to build a model &#10004 </li> 
    <li> Understand and implement a Seq2Seq neural network model </li>
    <li> After, allow the model to use given data from a file and answer prompts that way </li>
</ol>

<h3> Notes: </h3>
    Throughout my research for this project I discovered a neural network model which is used for
    language input and output called Seq2Seq. I will use this model in "Encoding and Decoding" the 
    user input with the expected output.
