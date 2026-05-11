// 13 - DOM Basics (Browser Only)
//
// The DOM (Document Object Model) is the browser's live tree of HTML elements.
// This file cannot be run with Node.js — paste snippets into the browser console
// or link this file from an HTML page with <script src="13_dom_basics.js"></script>


// =========================================================
// SELECTING ELEMENTS
// =========================================================

// querySelector returns the FIRST matching element (CSS selector syntax)
const heading = document.querySelector("h1");
const btn     = document.querySelector("#submit-btn");   // by id
const items   = document.querySelectorAll(".list-item"); // NodeList of ALL matches

// Older but still common
const byId    = document.getElementById("app");
const byTag   = document.getElementsByTagName("p");      // HTMLCollection (live)


// =========================================================
// READING AND WRITING CONTENT
// =========================================================

// textContent — plain text (safe; never parses HTML)
heading.textContent = "New Title";

// innerHTML — parses HTML (use with caution; never insert user input directly)
document.querySelector(".container").innerHTML = "<p>Hello <strong>World</strong></p>";

// Attributes
btn.setAttribute("disabled", "true");
btn.removeAttribute("disabled");
console.log(btn.getAttribute("type")); // "button"

// Style
heading.style.color      = "royalblue";
heading.style.fontSize   = "2rem";


// =========================================================
// CLASSLIST — add/remove/toggle CSS classes
// =========================================================

const card = document.querySelector(".card");
card.classList.add("active");
card.classList.remove("hidden");
card.classList.toggle("highlighted");    // add if absent, remove if present
console.log(card.classList.contains("active")); // true


// =========================================================
// CREATING AND INSERTING ELEMENTS
// =========================================================

function createListItem(text) {
    const li = document.createElement("li");
    li.textContent = text;
    li.classList.add("list-item");
    return li;
}

const ul = document.querySelector("ul");
ul.append(createListItem("First"));   // append at end
ul.prepend(createListItem("Zero"));   // insert at start

// Insert relative to a reference element
const ref = ul.children[1];
ref.before(createListItem("Before ref"));
ref.after(createListItem("After ref"));

// Remove an element
ul.querySelector(".remove-me")?.remove();


// =========================================================
// EVENTS
// =========================================================

btn.addEventListener("click", function (event) {
    console.log("Clicked!", event.target);
    event.preventDefault(); // stop default browser behavior (e.g. form submit)
});

// Arrow functions work too, but cannot access 'this' as the element
btn.addEventListener("mouseenter", (e) => {
    e.target.style.opacity = "0.8";
});

// Remove a listener (must pass the same function reference)
function handleKeydown(e) {
    if (e.key === "Escape") document.querySelector(".modal").classList.add("hidden");
}
document.addEventListener("keydown", handleKeydown);
// Later: document.removeEventListener("keydown", handleKeydown);


// =========================================================
// EVENT DELEGATION — attach ONE listener to a parent instead of many children
// =========================================================

// Instead of adding a click listener to every list item:
ul.addEventListener("click", (e) => {
    const item = e.target.closest("li"); // walk up to find the list item
    if (!item) return;
    item.classList.toggle("selected");
    console.log("Selected:", item.textContent);
});


// =========================================================
// FETCHING DATA AND UPDATING THE DOM
// =========================================================

async function loadPosts() {
    const response = await fetch("https://jsonplaceholder.typicode.com/posts?_limit=3");
    const posts    = await response.json();
    const list     = document.querySelector("#posts");

    for (const post of posts) {
        const li = document.createElement("li");
        li.textContent = post.title;
        list.append(li);
    }
}

// loadPosts(); // call this once the page is loaded
