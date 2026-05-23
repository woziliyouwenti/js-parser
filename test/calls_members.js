// Calls, member access, new expressions, and nested indexing

var user = {
    profile: {
        name: "Ada",
        scores: [95, 88, 76]
    }
};

var firstScore = user.profile.scores[0];
var secondScore = user["profile"].scores[1];
var message = formatter.format(user.profile.name, firstScore);
var created = new Result(message, firstScore);

console.log(formatter.format("done", created.value));

