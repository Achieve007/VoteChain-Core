document.addEventListener('DOMContentLoaded', function() {
    // Current year for footer
    document.getElementById('year').textContent = new Date().getFullYear();
    
    // Mobile menu toggle
    const hamburger = document.querySelector('.hamburger');
    const navList = document.querySelector('.nav-list');
    
    hamburger.addEventListener('click', function() {
        this.classList.toggle('active');
        navList.classList.toggle('active');
    });
    
    // Close mobile menu when clicking a nav link
    document.querySelectorAll('.nav-link').forEach(link => {
        link.addEventListener('click', function() {
            hamburger.classList.remove('active');
            navList.classList.remove('active');
        });
    });
    
    // Back to top button
    const backToTopBtn = document.querySelector('.back-to-top');
    
    window.addEventListener('scroll', function() {
        if (window.pageYOffset > 300) {
            backToTopBtn.classList.add('active');
        } else {
            backToTopBtn.classList.remove('active');
        }
    });
    
    // Smooth scroll for all links
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function(e) {
            e.preventDefault();
            
            const targetId = this.getAttribute('href');
            if (targetId === '#') return;
            
            const targetElement = document.querySelector(targetId);
            if (targetElement) {
                window.scrollTo({
                    top: targetElement.offsetTop - 80,
                    behavior: 'smooth'
                });
            }
        });
    });
    
    // Dark/Light mode toggle
    const themeToggle = document.getElementById('theme-toggle');
    const themeIcon = themeToggle.querySelector('i');
    
    // Check for saved theme preference or use preferred color scheme
    const savedTheme = localStorage.getItem('theme');
    const prefersDark = window.matchMedia('(prefers-color-scheme: dark)').matches;
    
    if (savedTheme === 'dark' || (!savedTheme && prefersDark)) {
        document.documentElement.setAttribute('data-theme', 'dark');
        themeIcon.classList.replace('fa-moon', 'fa-sun');
    }
    
    themeToggle.addEventListener('click', function() {
        const currentTheme = document.documentElement.getAttribute('data-theme');
        
        if (currentTheme === 'dark') {
            document.documentElement.removeAttribute('data-theme');
            themeIcon.classList.replace('fa-sun', 'fa-moon');
            localStorage.setItem('theme', 'light');
        } else {
            document.documentElement.setAttribute('data-theme', 'dark');
            themeIcon.classList.replace('fa-moon', 'fa-sun');
            localStorage.setItem('theme', 'dark');
        }
    });
    
    // Load projects from JSON
    fetchProjects();
    
    // Load skills from JSON
    fetchSkills();
    
    // Contact form handling
    const contactForm = document.getElementById('contact-form');
    const formMessage = document.getElementById('form-message');
    
    contactForm.addEventListener('submit', function(e) {
        e.preventDefault();
        
        // Get form values
        const name = document.getElementById('name').value;
        const email = document.getElementById('email').value;
        const subject = document.getElementById('subject').value;
        const message = document.getElementById('message').value;
        
        // Simple validation
        if (!name || !email || !message) {
            showFormMessage('Please fill in all required fields', 'error');
            return;
        }
        
        // Here you would typically send the form data to a server
        // For this template, we'll just simulate a successful submission
        showFormMessage('Thank you for your message! I will get back to you soon.', 'success');
        contactForm.reset();
        
        // In a real implementation, you would use fetch() to send the data to your backend
        /*
        fetch('your-backend-endpoint', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                name: name,
                email: email,
                subject: subject,
                message: message
            }),
        })
        .then(response => response.json())
        .then(data => {
            showFormMessage('Thank you for your message! I will get back to you soon.', 'success');
            contactForm.reset();
        })
        .catch(error => {
            showFormMessage('There was an error sending your message. Please try again later.', 'error');
        });
        */
    });
    
    function showFormMessage(text, type) {
        formMessage.textContent = text;
        formMessage.style.display = 'block';
        formMessage.className = type;
        
        setTimeout(() => {
            formMessage.style.display = 'none';
        }, 5000);
    }
});

// Load projects from JSON file
async function fetchProjects() {
    try {
        // In a real implementation, you would fetch from a JSON file
        // const response = await fetch('data/projects.json');
        // const projects = await response.json();
        
        // For this template, we'll use a hardcoded array
        const projects = [
            {
                "id": 1,
                "title": "E-commerce Website",
                "category": "web",
                "description": "A fully responsive e-commerce website with product filtering, cart functionality, and secure checkout.",
                "image": "images/project1.jpg",
                "links": [
                    {"type": "demo", "url": "#"},
                    {"type": "code", "url": "#"}
                ]
            },
            {
                "id": 2,
                "title": "Task Management App",
                "category": "app",
                "description": "A productivity application for managing tasks with drag-and-drop functionality and team collaboration features.",
                "image": "images/project2.jpg",
                "links": [
                    {"type": "demo", "url": "#"},
                    {"type": "code", "url": "#"}
                ]
            },
            {
                "id": 3,
                "title": "Portfolio Design",
                "category": "design",
                "description": "Modern portfolio design with clean aesthetics and smooth animations for creative professionals.",
                "image": "images/project3.jpg",
                "links": [
                    {"type": "demo", "url": "#"},
                    {"type": "code", "url": "#"}
                ]
            },
            {
                "id": 4,
                "title": "Weather Dashboard",
                "category": "web",
                "description": "Real-time weather dashboard showing current conditions and forecasts using data from a weather API.",
                "image": "images/project4.jpg",
                "links": [
                    {"type": "demo", "url": "#"},
                    {"type": "code", "url": "#"}
                ]
            },
            {
                "id": 5,
                "title": "Fitness Tracker",
                "category": "app",
                "description": "Mobile application for tracking workouts, nutrition, and progress with data visualization.",
                "image": "images/project5.jpg",
                "links": [
                    {"type": "demo", "url": "#"},
                    {"type": "code", "url": "#"}
                ]
            },
            {
                "id": 6,
                "title": "Brand Identity",
                "category": "design",
                "description": "Complete brand identity design including logo, color palette, typography, and brand guidelines.",
                "image": "images/project6.jpg",
                "links": [
                    {"type": "demo", "url": "#"},
                    {"type": "code", "url": "#"}
                ]
            }
        ];
        
        displayProjects(projects);
        setupProjectFilter(projects);
    } catch (error) {
        console.error('Error loading projects:', error);
    }
}

function displayProjects(projects) {
    const projectsContainer = document.getElementById('projects-container');
    
    projectsContainer.innerHTML = projects.map(project => `
        <div class="project-card" data-category="${project.category}">
            <img src="${project.image}" alt="${project.title}" class="project-img" loading="lazy">
            <div class="project-content">
                <h3 class="project-title">${project.title}</h3>
                <span class="project-category">${project.category}</span>
                <p class="project-description">${project.description}</p>
                <div class="project-links">
                    ${project.links.map(link => `
                        <a href="${link.url}" class="project-link">
                            <i class="fas fa-${link.type === 'demo' ? 'eye' : 'code'}"></i>
                            ${link.type === 'demo' ? 'Demo' : 'Code'}
                        </a>
                    `).join('')}
                </div>
            </div>
        </div>
    `).join('');
}

function setupProjectFilter(projects) {
    const filterButtons = document.querySelectorAll('.filter-btn');
    
    filterButtons.forEach(button => {
        button.addEventListener('click', function() {
            // Update active button
            filterButtons.forEach(btn => btn.classList.remove('active'));
            this.classList.add('active');
            
            const filter = this.getAttribute('data-filter');
            const projectCards = document.querySelectorAll('.project-card');
            
            projectCards.forEach(card => {
                if (filter === 'all' || card.getAttribute('data-category') === filter) {
                    card.style.display = 'block';
                } else {
                    card.style.display = 'none';
                }
            });
        });
    });
}

// Load skills from JSON file
async function fetchSkills() {
    try {
        // In a real implementation, you would fetch from a JSON file
        // const response = await fetch('data/skills.json');
        // const skills = await response.json();
        
        // For this template, we'll use a hardcoded array
        const skills = [
            {
                "name": "HTML5",
                "icon": "fab fa-html5",
                "level": 95
            },
            {
                "name": "CSS3",
                "icon": "fab fa-css3-alt",
                "level": 90
            },
            {
                "name": "JavaScript",
                "icon": "fab fa-js",
                "level": 85
            },
            {
                "name": "React",
                "icon": "fab fa-react",
                "level": 80
            },
            {
                "name": "Node.js",
                "icon": "fab fa-node-js",
                "level": 75
            },
            {
                "name": "Git",
                "icon": "fab fa-git-alt",
                "level": 85
            },
            {
                "name": "UI/UX Design",
                "icon": "fas fa-pencil-ruler",
                "level": 70
            },
            {
                "name": "Responsive Design",
                "icon": "fas fa-mobile-alt",
                "level": 90
            }
        ];
        
        displaySkills(skills);
    } catch (error) {
        console.error('Error loading skills:', error);
    }
}

function displaySkills(skills) {
    const skillsContainer = document.getElementById('skills-container');
    
    skillsContainer.innerHTML = skills.map(skill => `
        <div class="skill-card">
            <div class="skill-icon">
                <i class="${skill.icon}"></i>
            </div>
            <h4 class="skill-name">${skill.name}</h4>
            <div class="skill-level">
                <div class="skill-level-bar" style="width: ${skill.level}%"></div>
            </div>
            <span class="skill-percent">${skill.level}%</span>
        </div>
    `).join('');
}