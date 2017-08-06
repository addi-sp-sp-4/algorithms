function txt2Bin(text, delimiter = "") {
    
    // Javascript strings are in UTF-16 by default;
    // This clever hack gives us UTF-8 support. It's a bit weird but very handy.
    
    
    text = unescape(encodeURIComponent(text));
    var length = text.length;
    var output = [];
    
    // toString(x): x defines the radix, so the base
    for (var i = 0; i < length; i++) {
        var bin = text[i].charCodeAt().toString(2);
        output.push(Array(8 - bin.length + 1).join("0") + bin);
  } 
  return output.join(delimiter);
}
function amountOfSubStringsInString(needle, haystack) {
    
    
    // Quick hack
    return haystack.split(needle).length - 1;
    
}


charTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
function base64Encode(input) {
    
    
    // Characters in the base64 character table
    charTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    // Convert the input to binary
    binary = txt2Bin(input);
    
    padding = binary.length % 6;
    
    
    // Split the binary string in groups of 6. This omits characters if the length of the binary string isn't dividable by 6, So we'll add it back later, with the padding base64 requires
    binaryArr = binary.match(/(......?)/g);
    
    appendage = "";
    
    
    // If the padding is needed, we first need to grab the part omitted from binaryArr, and append the padding to it. We'll also construct the appendage of '='s needed at the very end now we are at it.
    if(padding != 0) {
        
        // Get said part omitted from binaryArr
        remains = binary.slice(binary.length - padding, binary.length);
        
        for(var i = 0; i < 6 - padding; i++) {
            remains += "0";
            
            // Little hack to add only half of the length of the padding to the appendage
            if(i % 2 == 0) {
                appendage += "=";
            }
        }
        // Push it to binaryArr
        binaryArr.push(remains);
    }
    
    result = "";
    
    // For every segment of six binary numbers, convert that segment to decimal and get the character in charTable at the index of said number.
    for(i = 0; i < binaryArr.length; i++) {
        
        // parseInt(n, x): x defines the radix, so the base.
        result += charTable[parseInt(binaryArr[i], 2)];
        
    }
    
    // Add the appendage to the result. If there was no padding, the appendage will just be an empty string
    result += appendage;
    
    return result;
    
}

function base64Decode(input) {
    
    // Characters in the base64 character table
    charTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    // Times 2 because every '=' equals 2 zeroes in the binary string.
    padding = amountOfSubStringsInString('=', input) * 2;
    
    // Remove the '='s 
    input = input.replace(/=/g, '');
    
    binary = "";
    
    for(var i = 0; i < input.length; i++) {
        
        // We are quite literally reversing the encoding algorithm (duh), so now we get the index again, and add the binary string to binary. 
        index = charTable.indexOf(input[i]) ;
        
        // !!! ATTENTION !!!
        // DO NOT USE txt2Bin() HERE, WE ARE NOT TRYING TO GET THE BINARY VALUE FROM A STRING WITH A DIGIT, BUT FROM AN INT.
        
        // Convert int to binary. 
        // toString(x): x is the radix, or base;
        // We need to prepend a zero because tostring is a bit fucky. It does not really put zeroes in front.
        segment = index.toString(2);

        for(var j = 0; j < segment.length % 6; j++) {
            segment = "0" + segment;
        }
        console.log(index, segment.length, segment);
        binary += segment;
    }
    // Remove padding if necessary
    
    if(padding != 0) {
        binary = binary.slice(0, binary.length - padding);
    }
    
    console.log(binary);
    
    
    result = "";
    // Split in groups of 8
    binaryArr = binary.match(/(........?)/g);
    
    // For every segment convert it to a character and add it to result
    for(var i = 0; i < binaryArr.length; i++) {
        result += String.fromCharCode(parseInt(binaryArr[i], 2));
    }
    return result;
    
}


















































